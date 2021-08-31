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
#ifndef  _SYS_INFO_H
#define  _SYS_INFO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define   SET_BIT(target,bit)          ((target)=((target)|(1<<(bit))))
#define   CLR_BIT(target,bit)          ((target)=((target)&(~(1<<(bit)))))
#define   CHK_BIT(target,bit)          (((target)&(1<<(bit)))?1:0)
#define   REV_BIT(target,bit)           ((target)= ((target)^(1<<(bit))))   //reservered bits

#define ALIGN(memSize, pad)   ((static_cast<int>((memSize) + pad - 1) / pad) * pad)

#define ARRAYSIZE(a)          (sizeof(a)/sizeof(a[0]))


#define  NO_WAIT             0
#define  WAIT_FOREVER       -1

#define  SEM_FULL            1
#define  SEM_EMPTY           0

#define  TIMER_NORMAL          0  //timer use only once
#define  TIMER_PERIOD          1  //time period
#define  SEC_UNIT              100 

typedef  void *    SEM_ID ;
typedef  void *    MSG_Q_ID ;

#ifdef _WINDOWS
#define  PTRACE(fmt,...) lib_message( __FILE__, __LINE__,fmt,__VA_ARGS__)
#else
#define  PTRACE(fmt,args...) lib_message( basename(__FILE__), __LINE__,fmt,##args)

#define _DEBUG(format, ...) fprintf(stderr, "[%s:%d/%s] " format "\n", basename(__FILE__), __LINE__, __FUNCTION__, ##__VA_ARGS__)
#endif

typedef void ( * TIMER_CALLBACK ) ( void * pdata ) ;
//typedef void ( * REAL_TIMER_CB ) ( int signo ) ;
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void os_sleep(int ms);


/******************************************************************
���������ʾ��ͨ��PTRACE�������ã�����ͬprintf
*******************************************************************/
void lib_message (const char *filename, int fileno, const char *fmt, ...);
///////////////////////////////////////////////////////////////////////////////

/* Function defined for MESSAGE  ���̼߳�ͨѶ*********************/
//#define  send_message_nowait( q , len , buf )   msgQSend( q , (char*)(buf) , len , NO_WAIT  )
#define  sys_send_message( q , buf , len )     msgQSend( q , (char*)(buf) , len , NO_WAIT  )
#define  sys_receive_message( q , buf , len )  msgQReceive( q , (char*)(buf) , len , WAIT_FOREVER  )

MSG_Q_ID msgQCreate( int maxMsgsNum, int maxMsgLength ) ;
int msgQSend       ( MSG_Q_ID msgQId ,  char * buffer,  int nBytes, int timeOut ) ;
int msgQReceive    ( MSG_Q_ID msgQId ,  char * buffer,  int maxNBytes,  int timeOut ) ;
int msgQDelete     ( MSG_Q_ID msgQId ) ;
int msgQNumMsgs    ( MSG_Q_ID msgQId ) ;
int sys_cancel_read(MSG_Q_ID msgQId);

//int msgQShow       ( MSG_Q_ID msgQId ) ;

///////////////////////////////////////////////////////////////////////////////
/*     Function defined for SEMAPHORE                                        */
SEM_ID semBCreate (  int initialState ) ;
SEM_ID semCCreate (  int initialCount ) ;
int    semGive    ( SEM_ID semId  ) ;
int    semTake    ( SEM_ID semId,  int    timeOut ) ;
int    semDelete  ( SEM_ID semId  ) ;

///////////////////////////////////////////////////////////////////////////////
/*****************udpͨ�Žӿ� ,���̼�ͨѶ*********************/
//just send udp data,no recv responst
int  send_udp_message   ( char * msg ,int len ,int port );//send msg 
int  recv_udp_message   ( char * msg ,int len ,int port );//send msg 

//send and resv msg to buf
int  send_recv_timeout( char * msg ,int len ,int port, char * recv_msg ,int recv_len, int second );

//recv udp second 
int  recv_with_timeout( int s , char * buf , int len , int second );

//send remote udp msg
int send_remote_udp( char * msg ,  int len , char * remote,int port );

//return: 0 ok,-1;error
int ping( char *ips, int timeout);
///////////////////////////////////////////////////////////////////////////////
/************************add timer interface**************************/
int  core_timer_init ( void ) ;

//�������ص������Ķ�ʱ������С��λ��10���룩
int  core_timer_start  ( int ms , int type , void *pdata , TIMER_CALLBACK func ) ;

int  core_timer_get_ticks( int timer) ;
void core_timer_stop ( int timer ) ;
void core_timer_reset( int timer ) ;
//pause 1: pause ,0 resume
void core_timer_pause( int timer , int pause ) ;
void core_timer_set  ( int timer , int ticks ) ;

//int GetIpAddr(char *IfName,unsigned int *IpAddr);
//int get_dns(char *dns);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif

