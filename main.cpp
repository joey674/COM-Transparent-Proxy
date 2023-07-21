#include "thread.h"


int main(int argc, char* argv[])    
{
    HANDLE hThread1, hThread2, hThread3, hThread4;
    DWORD dwThreadId1, dwThreadId2, dwThreadId3, dwThreadId4;

    HANDLE hVirtualDev = PORT_open(L"COM2", NULL);
    HANDLE hOutputDev = PORT_open(L"COM7", NULL);


    if (hVirtualDev == NULL || hOutputDev == NULL)
        return -1;

    if (!PORT_set(hVirtualDev) || !PORT_set(hOutputDev))
        return -1;

    if (!Smp_init())
        return -1;

    if (!Log_init())
        return -1;


    printf("init successful.\n");



    hThread1 = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)thread_read_from_service, 
        hVirtualDev,  
        0,
        &dwThreadId1);
    if (hThread1 == NULL) {
        printf("Error: unable to create thread_read_from_service.\n");
        ExitProcess(1);
    }

    hThread4 = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)thread_write_to_device,
        hOutputDev,
        0,
        &dwThreadId4);
    if (hThread4 == NULL) {
        printf("Error: unable to create thread_write_to_device.\n");
        ExitProcess(1);
    }

    hThread2 = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)thread_write_to_service,
        hVirtualDev,
        0,
        &dwThreadId2);
    if (hThread2 == NULL) {
        printf("Error: unable to create thread_write_to_service.\n");
        ExitProcess(1);
    }
    
    hThread3 = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)thread_read_from_device, 
        hOutputDev,
        0,
        &dwThreadId3);
    if (hThread3 == NULL) {
        printf("Error: unable to create thread_read_from_device\n");
        ExitProcess(1);
    }


    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread4, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);
    WaitForSingleObject(hThread3, INFINITE);
  

}    