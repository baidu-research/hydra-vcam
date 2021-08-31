// SPDX-License-Identifier: Apache-2.0
//
#include "common.h"
#include "sdk.h"
#include "cameraCtrl.h"


struct MESSAGE_MAP
{
	long message;
	int (*msg_handle) ( KERNEL_MESSAGE* msg,int sock,struct sockaddr * addr,socklen_t  addr_len);
};

static int OnGetVersion(KERNEL_MESSAGE* msg,int sock,struct sockaddr * addr,socklen_t  addr_len)
{
 	int len=sprintf(msg->data,"%s-date:%s",VERSION,__DATE__);
	msg->length=len;				
	return	sendto( sock , (char*)msg , sizeof(MESSAG_HEADER) + msg->length  , 0 ,addr , addr_len ) ; 		
}

static int OnVideoControl(KERNEL_MESSAGE* msg,int sock,struct sockaddr * addr,socklen_t  addr_len)
{
	int capmode=msg->data[0];
	PTRACE("recv video control command %d",capmode);
	msg->data[0]=1;
	msg->length=1;				
	sendto( sock , (char*)msg , sizeof(MESSAG_HEADER) + msg->length  , 0 ,addr , addr_len ) ; 
#if  1	
 	if (capmode>0) //open
 	{
 		//	if (get_ncc_status())
 			//	close_ncc();
 			PTRACE("please open ncc!%d",capmode);	
 		 open_ncc(capmode);
 	}
 	else
 	{
 		PTRACE("please close ncc!");	
 		close_ncc();
 	}
#endif 	
	return 0;	
}

static int OnOcrReport(KERNEL_MESSAGE* msg,int sock,struct sockaddr * addr,socklen_t  addr_len)
{
	PTRACE("recv ocr report %s",msg->data);
	strcpy(g_ocr_res,msg->data);
	msg->data[0]=1;
	msg->length=1;				
	return sendto( sock , (char*)msg , sizeof(MESSAG_HEADER) + msg->length  , 0 ,addr , addr_len ) ; 		
}

static struct MESSAGE_MAP msg_maps[]={
		{APP_GET_VERSION,OnGetVersion},
		{APP_VIDEO_CONTROL,OnVideoControl},
		{APP_OCR_RES_DATA,OnOcrReport},
};

void*  sys_ctrl_loop( void *arg)
{
	KERNEL_MESSAGE msg ;
	int val,ret;
	int udp_server;
	int addr_len;
	struct sockaddr_in addr ;

	val = 1;
	addr_len = sizeof(struct sockaddr);
	addr.sin_family      = AF_INET       ;
	addr.sin_addr.s_addr = htonl ( INADDR_ANY ) ;
	addr.sin_port        = htons ( MAIN_CTRL_PORT) ;
	
	udp_server  = socket( AF_INET, SOCK_DGRAM, 0 );
	setsockopt( udp_server , SOL_SOCKET , SO_REUSEADDR , &val , sizeof(int) ) ;
	if( bind  ( udp_server , ( struct sockaddr *)&addr , addr_len ) < 0 )
	{
	        PTRACE("start_network: Bind UDP PORT[%d] Error ." , MAIN_CTRL_PORT ) ;
	        close(udp_server);
	        return NULL;
  }
  PTRACE("start_network: Bind UDP PORT[%d] OK ." , MAIN_CTRL_PORT  ) ;
	while(core_context->running)
	{
		memset(&msg,0,sizeof(msg));
 		ret = recvfrom(udp_server, (char*)&msg, sizeof(KERNEL_MESSAGE), 0,
                       (struct sockaddr *)&addr, (socklen_t *)&addr_len);
    if ( ret <= 0 && errno != EINTR )
       // break;
       continue;
	
    if ( ret < (int)sizeof(MESSAG_HEADER))
        continue;        
        
    PTRACE("receive msg = = 0x%6x,len=%d from %d",msg.command,msg.length,msg.sender);   
    SWAP(msg.sender,msg.receiver);
    
		int i=0;
		for ( i=0;i<ARRAYSIZE(msg_maps);i++)
		{
				if (msg_maps[i].message==msg.command )
				{
					 int ret=msg_maps[i].msg_handle(&msg,udp_server,(struct sockaddr *)&addr , addr_len);
					 if (ret<0)
					 		PTRACE("handle error for command=%d",msg.command);
					 break;
				}
		}
		if  (i==ARRAYSIZE(msg_maps))
			PTRACE("Not support this command=0x%6x yet!",msg.command);	
  }
  PTRACE("*****exit thread %s*****",__FUNCTION__);
  return NULL;
}

