#include "utils.h"

HANDLE  hSmpVirCom = NULL;
HANDLE  hSmpCom = NULL;

std::ofstream log_service;
std::ofstream log_device;

char buffer_service[LOG_BUFFER_SIZE];
char buffer_device[LOG_BUFFER_SIZE];

bool Smp_init() {
    hSmpVirCom = CreateSemaphoreW(NULL, 1, 1, NULL);
    hSmpCom = CreateSemaphoreW(NULL, 1, 1, NULL);

    if (hSmpVirCom == nullptr)
    {
        printf("Error: Failed to create semaphore.\n");
        return FALSE;
    }
    if (hSmpCom == nullptr)
    {
        printf("Error: Failed to create semaphore.\n");
        return FALSE;
    }

    return TRUE;
}

bool Log_init() {

    if (!CreateDirectoryA("./logFile", NULL)) {
        if (GetLastError() == ERROR_ALREADY_EXISTS) {

        }
        else if (GetLastError() == ERROR_PATH_NOT_FOUND)
        {
            std::cout << "Error: Failed to create directory. Invalid path.";
        }
        else
        {
            std::cout << "Error: Failed to create directory.";
        }
    }

    auto t = std::time(nullptr);
    std::tm tm;

    errno_t err = localtime_s(&tm, &t);
    if (err) {
        return FALSE;
    }

    std::ostringstream log_s;
    std::ostringstream log_d;

    log_s << "./logFile/" << std::put_time(&tm, "serviceLog_%m%d_%H%M%S");
    log_d << "./logFile/" << std::put_time(&tm, "deviceLog_%m%d_%H%M%S");

    log_service.open(log_s.str());
    log_device.open(log_d.str());

    log_service.rdbuf()->pubsetbuf(buffer_service, sizeof buffer_service);
    log_device.rdbuf()->pubsetbuf(buffer_device, sizeof buffer_device);

    if (!log_service || !log_device) {
        printf("Error: Failed to create logFile.\n");
        return FALSE;
    }

    return TRUE;
}