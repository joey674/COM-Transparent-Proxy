#pragma once
#include "serialPort.h" 
#include "ringBuffers.h"
#include "utils.h"

extern ringBuffer* ringBuffer_Out;
extern ringBuffer* ringBuffer_In;

extern HANDLE  hSmpVirCom;
extern HANDLE  hSmpCom;

extern std::ofstream log_service;
extern std::ofstream log_device;


DWORD
WINAPI
thread_read_from_service(HANDLE hDev) {
    int i = 0;
    DWORD bytes_read_from_service = 0;
    DWORD bytes_write_in_buffer = 0;
    //uint8_t buf[BUFFER_SIZE] = { 0 };
    uint8_t* buf = new uint8_t[BUFFER_SIZE]();
    DWORD errors;
    COMSTAT status;

    while (1) {
        bytes_read_from_service = 0;
        bytes_write_in_buffer = 0;
        std::memset(buf, 0, BUFFER_SIZE);

        if (!ClearCommError(hDev, &errors, &status)) {
            printf("Error checking COM port status: %d\n", GetLastError());
            return -1;
        }
        if (status.cbInQue > 0) {
            WaitForSingleObject(hSmpVirCom, INFINITE);
            ReadFile(hDev, buf, BUFFER_SIZE, &bytes_read_from_service, NULL);
            ReleaseSemaphore(hSmpVirCom, 1, NULL);
            printf("---%d bytes_read_from_service.", bytes_read_from_service);

            bytes_write_in_buffer = nwrite(ringBuffer_Out, buf, bytes_read_from_service);

            if (bytes_write_in_buffer != bytes_read_from_service) {
                printf("*********Error: write_to_Outbuffer.**********\n");
            }
        }
    }
    return 0;
}

DWORD
WINAPI
thread_write_to_device(HANDLE hDev) {
    int i = 0;
    DWORD bytes_read_from_buffer = 0;
    DWORD bytes_write_to_device = 0;
    uint8_t* buf = new uint8_t[BUFFER_SIZE](); 

    while (1) {
        bytes_read_from_buffer = 0;
        bytes_write_to_device = 0;
        std::memset(buf, 0, BUFFER_SIZE);

        if (nreadable(ringBuffer_Out) > 0) {
            bytes_read_from_buffer = nread(ringBuffer_Out, buf, BUFFER_SIZE);

            std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
            auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
            uint8_t binary_timestamp[sizeof(timestamp)];
            std::memcpy(binary_timestamp, &timestamp, sizeof(timestamp));
            log_service.write(reinterpret_cast<const char*>(binary_timestamp), sizeof(binary_timestamp));

            log_service.write(reinterpret_cast<const char*>(buf), bytes_read_from_buffer);        

            WaitForSingleObject(hSmpCom, INFINITE);
            WriteFile(hDev, buf, bytes_read_from_buffer, &bytes_write_to_device, NULL);
            ReleaseSemaphore(hSmpCom, 1, NULL);

            if (bytes_read_from_buffer != bytes_write_to_device) {
                printf("**********Error: write_to_service**********\n");
            }
            else {
                printf("%d bytes_write_to_device.---\n", bytes_write_to_device);
            }
        }
    }
    return 0;
}

DWORD
WINAPI
thread_write_to_service(HANDLE hDev) {
    int i = 0;
    DWORD bytes_read_from_buffer = 0;
    DWORD bytes_write_to_service = 0;
    uint8_t* buf = new uint8_t[BUFFER_SIZE]();

    while (1) {
        bytes_read_from_buffer = 0;
        bytes_write_to_service = 0;
        std::memset(buf, 0, BUFFER_SIZE);
        
        if (nreadable(ringBuffer_In) > 0) {
            bytes_read_from_buffer = nread(ringBuffer_In, buf, BUFFER_SIZE);
            log_device.write(reinterpret_cast<const char*>(buf), bytes_read_from_buffer);

            WaitForSingleObject(hSmpVirCom, INFINITE);
            WriteFile(hDev, buf, bytes_read_from_buffer, &bytes_write_to_service, NULL);
            ReleaseSemaphore(hSmpVirCom, 1, NULL);
            if (bytes_read_from_buffer != bytes_write_to_service) {
                printf("\n**********Error: write_to_service.**********\n");
            }
            else {
                printf("%d bytes_write_to_service.\n", bytes_write_to_service);
            }
        }
    }
    return 0;
}

DWORD
WINAPI
thread_read_from_device(HANDLE hDev) {
    int i = 0;
    DWORD bytes_read_from_device = 0;
    DWORD bytes_write_in_buffer = 0;
    uint8_t* buf = new uint8_t[BUFFER_SIZE]();
    DWORD errors;
    COMSTAT status;

    while (1) {
        bytes_read_from_device = 0;
        bytes_write_in_buffer = 0;
        std::memset(buf, 0, BUFFER_SIZE);

        if (!ClearCommError(hDev, &errors, &status)) {
            printf("Error checking COM port status: %d\n", GetLastError());
            return -1;
        }
        if (status.cbInQue > 0) {
            WaitForSingleObject(hSmpCom, INFINITE);
            ReadFile(hDev, buf, BUFFER_SIZE, &bytes_read_from_device, NULL);
            ReleaseSemaphore(hSmpCom, 1, NULL);
            printf("%d bytes_read_from_device.", bytes_read_from_device);

            bytes_write_in_buffer = nwrite(ringBuffer_In, buf, bytes_read_from_device);            
            if (bytes_write_in_buffer != bytes_read_from_device) 
                printf("\n**********Error: bytes_write_to_Inbuffer.**********\n");
        }
    }
    return 0;
}



