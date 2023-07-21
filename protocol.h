#pragma once
#ifndef _PROTOCOL_H
#define _PROTOCOL_H

   
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <cstring>s
#include <winsock2.h>
#include <windows.h>
#include <winbase.h>



#define BAUDRATE 115200
#define BUFFER_SIZE			1 * 1024 * 1024 
#define RING_BUFFER_SIZE	5 * 1024 * 1024 
#define COMM_BUFFER_SIZE	1 * 1024 * 1024
#define LOG_BUFFER_SIZE		1 * 1024 * 1024


#endif
