#pragma once
#ifndef  _SERIALPORT_H
#define  _SERIALPORT_H
 
  
#include "protocol.h"  
     

HANDLE PORT_open(LPCTSTR port,DWORD flag);
bool PORT_close(HANDLE hDev) ;
bool PORT_set(HANDLE hDev);
bool PORT_check(HANDLE hDev);
bool PORT_recv(HANDLE hDev, void *rcv_buf);
bool PORT_send(HANDLE hDev, void *send_buf);

 
#endif