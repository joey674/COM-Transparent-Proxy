#include"serialPort.h"


HANDLE PORT_open(LPCTSTR port, DWORD flag) {
    HANDLE hDev = NULL;
    if (flag == NULL) {
        hDev = CreateFile(port,
            GENERIC_READ | GENERIC_WRITE,
            NULL,
            NULL,
            OPEN_EXISTING,
            NULL,
            NULL);
    }
    else if (flag == FILE_FLAG_OVERLAPPED) {
        hDev = CreateFile(port,
            GENERIC_READ | GENERIC_WRITE,
            NULL,
            NULL,
            OPEN_EXISTING,
            FILE_FLAG_OVERLAPPED,
            NULL);
    }

    if (hDev == INVALID_HANDLE_VALUE || hDev == NULL) {
        printf("Error opening port:%p.\n", port);
        return NULL;
    }
    else {
        printf("opening port successful.\n");
    }
    return hDev;
}

bool PORT_close(HANDLE hDev) {
    CloseHandle(hDev);
    return TRUE;
}

bool PORT_set(HANDLE hDev) {
    SetupComm(hDev, COMM_BUFFER_SIZE, COMM_BUFFER_SIZE);

    DCB dcbSerialParams = { 0 };
    if (!GetCommState(hDev, &dcbSerialParams)) {
        printf("Error getting current state of the device.\n");
        return FALSE;
    }
    dcbSerialParams.BaudRate = BAUDRATE;
    if (!SetCommState(hDev, &dcbSerialParams)) {
        printf("Error setting serial port state.\n");
        return FALSE;
    }

    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout = MAXDWORD;
    timeouts.ReadTotalTimeoutConstant = 0;
    timeouts.ReadTotalTimeoutMultiplier = 0;
    SetCommTimeouts(hDev, &timeouts);

    return TRUE;
}

bool PORT_check(HANDLE hDev) {
    //OVERLAPPED overlapped = { 0 };
    //overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    //DWORD eventMask;
    //SetCommMask(hDev, EV_RXCHAR);
    //if (!WaitCommEvent(hDev, &eventMask, &overlapped)) {
    //    if (GetLastError() != ERROR_IO_PENDING) {
    //        CloseHandle(overlapped.hEvent);
    //        return false;
    //    }
    //}
    //else if (!(eventMask & EV_RXCHAR)) {
    //    CloseHandle(overlapped.hEvent);
    //    return false;
    //}

    //DWORD dwRes = WaitForSingleObject(overlapped.hEvent, 100);
    //CloseHandle(overlapped.hEvent);
    //if (dwRes == WAIT_OBJECT_0) {
    //    return true;
    //}
    return false;
}

bool PORT_recv(HANDLE hDev, void* rcv_buf) {
    //return ReadFile(hDev, rcv_buf, 1, NULL, &olRead);
    return 0;
}

bool PORT_send(HANDLE hDev, void* send_buf) {
    //return WriteFile(hDev, send_buf, 1, NULL, &olWrite);
    return 0;
}