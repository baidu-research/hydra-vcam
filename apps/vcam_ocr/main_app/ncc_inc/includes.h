/*

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef INCLUDE_H_
#define INCLUDE_H_

#include <stdio.h> 
#include <ctype.h> 
#include <errno.h> 

#ifndef _WINDOWS
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <sys/file.h> 
#include <arpa/inet.h>
#include <netdb.h> 
#include <sys/ioctl.h> 
#include <sys/time.h>
#include <sys/shm.h> 
#else
#include <windows.h>
typedef int socklen_t;
#endif

#include <string.h> 
#include <pthread.h>

#include <sys/types.h> 

#include <stdlib.h>
#include <stdarg.h>
#include<sys/stat.h>
#include <stdint.h>
#include <pthread.h>
#include <stddef.h>

#define BYTE uint8_t
#define INT8U uint8_t
#define INT16U uint16_t
#define INT16 int16_t
#define INT32U uint32_t
#define INT32 int32_t
#define UINT  uint32_t
#define BOOL  unsigned char 


#define SUCCESS            0
#define FAILED             -1
#define FALSE              0
#define TRUE               1

#define  _PACKED_			__attribute__((packed))   //���ֽ��ڴ�λ����

#endif

