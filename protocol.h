#pragma once
#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include <stdio.h>      
#include <stdlib.h> 
#include <stdint.h>       
#include <fcntl.h>        
#include <errno.h>        
#include <string.h> 
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <process.h>        
#include <stdbool.h>
#include <chrono>
#include <cstring>

#include <winsock2.h>
#include <windows.h>
#include <winbase.h>



#define BAUDRATE 115200
#define BUFFER_SIZE			1 * 1024 * 1024 
#define RING_BUFFER_SIZE	10 * 1024 * 1024 
#define COMM_BUFFER_SIZE	1 * 1024 * 1024
#define LOG_BUFFER_SIZE		7 * 1024 * 1024

#define COMMUNI_SIZE 256

#endif
