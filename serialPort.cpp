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

