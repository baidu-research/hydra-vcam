// SPDX-License-Identifier: Apache-2.0
//
#include "common.h"
#include "param_struct.h"
#include <list>
#include <mutex> 
//#include "times.hpp"
#include "inifile.h"
#include "cameraCtrl.h"
#define MAX_CLI 10

//static 	 int clientfd[MAX_CLI];
typedef std::list<int> LISTFD;
static LISTFD clientfds;

std::mutex m_mutex; 
	
static int readblock(int sockfd,char* buf,int size)
{
	int iolen,nleft,index;
	
	nleft = size;
	index = 0;

	while(nleft > 0)
	{
		iolen = recv(sockfd,buf+index,nleft,0);
		if (iolen == 0) 
		{			
			PTRACE("client close connection!error=%d.",errno);
			return 0;//client close
		}

		if (iolen < 0) 
		{
			if (errno == EINTR) continue;

			PTRACE("recv error!error=%d.",errno);
			return iolen;
		}

		index += iolen;
		nleft -= iolen;
	}
	return index;	
}

static int writeblock(int fd, char* buffer, int len)
{
	int writeleft = len;
	int writelen = 0;
	while (writeleft > 0)
	{
		writelen = send(fd, buffer+(len-writeleft), writeleft,0);
		if (writelen <= 0)
		{
			if (errno == EINTR)
				continue;
			else
				return -1;
		}
		writeleft -= writelen;	
	}
	return 0;
}

static int send_update_cmd(const char* flilename)
{
	KERNEL_MESSAGE msg;
	memcpy(&msg.data,flilename,strlen(flilename));
	msg.command=SYS_APP_UPDATE;
	msg.receiver=WT_APP_MOD;
	msg.sender=CORE_APP_MOD;
	msg.length=strlen(flilename);
	PTRACE(" send update cmd to wtdog!%s",flilename);
	int ret = send_recv_timeout((char*)&msg, sizeof(MESSAG_HEADER) + msg.length,WT_CTRL_PORT,
														(char*)&msg,sizeof(msg),20);
														
	if (ret<0)
		 return ret;
  else 
  	 return msg.data[0];														
}

int  meta_relay(char* buf,int size)
{
	int ret=0;
	MESSAG_HEADER msg;

	msg.command=APP_REP_MEDIA;
	msg.receiver=REMOTE_CLI_MOD;
	msg.sender=CORE_APP_MOD;
	msg.length = size;
		
	std::lock_guard<std::mutex> lg(m_mutex);
	LISTFD::iterator it;  
	for (it = clientfds.begin(); it != clientfds.end(); it++) 
	{
		ret = writeblock( *it , (char*)&msg , sizeof(msg) );
		ret = writeblock( *it , buf , size ) ; 
	}	
	return 0;
}

struct MESSAGE_MAP
{
	long message;
	int (*msg_handle) ( KERNEL_MESSAGE* msg,int usersockfd);
};

static int OnGetVersion(KERNEL_MESSAGE* cmd,int usersockfd)
{
	char fw[100]={0};
	device_control_get_fw_version(fw,sizeof(fw));
	int len=sprintf(cmd->data,"%s-%s-date:%s",VERSION,fw,__DATE__);
	cmd->length=len;
	PTRACE("return version %s",cmd->data);
	return writeblock( usersockfd , (char*)cmd , sizeof(MESSAG_HEADER) + cmd->length ) ; 	 		
}

static int OnHeartTest(KERNEL_MESSAGE* cmd,int usersockfd)  //no need ack
{
	PTRACE("recv APP_HEART_TEST");
	return 0;
}

static int nwrite_file(FILE* fp, char* buffer, int len)
{
	int writeleft = len;
	int writelen = 0;
	while (writeleft > 0)
	{
		writelen = fwrite( buffer+(len-writeleft),1, writeleft,fp);
		if (writelen <=0)
		{
			PTRACE("wite file len:%d error: %s!",len,strerror(errno));
			return -1;
		}
		writeleft -= writelen;	
	}
	return 0;
}

static FILE* up_file=NULL;
static struct update_info upinfo;
static int   recv_size=0;
static char  up_buffer[2048];

static int OnUpdateStart(KERNEL_MESSAGE* cmd,int usersockfd)//prepare for upgrade 
{
		memcpy(&upinfo,cmd->data,sizeof(upinfo));
		
		cmd->data[0]=1;
		PTRACE("start update!need update file %s size=%d type=%d....",upinfo.AI_name,  \
						upinfo.file_size,upinfo.file_type);
		
		cmd->length=1;					
		
		if (upinfo.file_type==EC_FILE)
			up_file =fopen(INSTALL_FILE,"w");
		else if (upinfo.file_type==AI_BLOB)
		{
			up_file =fopen(AI_BLOB_FILE,"w");
			write_profile_string("AI_MODE","ai_name",upinfo.AI_name,"config.ini");
		}
		else if (upinfo.file_type==AI_BIN)
			up_file =fopen(AI_BIN_FILE,"w");
		else if (upinfo.file_type==AI_XML)
			up_file =fopen(AI_XML_FILE,"w");
		else
			cmd->data[0]=0;
										 		
		return writeblock( usersockfd , (char*)cmd , sizeof(MESSAG_HEADER) + cmd->length ) ; //ack  first,can send file now	
}

static int OnUpdateApp(KERNEL_MESSAGE* cmd,int usersockfd)
{	
		int ret=0;
		int block_size=cmd->length;
		recv_size+= block_size;
		PTRACE("recv update typ =%d  size=%d total recv size=%d",upinfo.file_type,block_size,recv_size);
		nwrite_file(up_file,up_buffer,block_size);
		if (recv_size>=upinfo.file_size)  //recv file ok then start update
		{
				char current_path[100];
				char filename[200];
				fclose(up_file);
			//	system("sync");
				cmd->data[0]=1;//ret;
				cmd->length=1;		
				recv_size = 0;
				up_file = NULL;		
				upinfo.file_size=0;			
				if (upinfo.file_type==EC_FILE)
				{
					getcwd(current_path, sizeof(current_path));
					sprintf(filename,"%s/%s",current_path,INSTALL_FILE);				
					ret=send_update_cmd(filename);
				}													
				return writeblock( usersockfd , (char*)cmd , sizeof(MESSAG_HEADER) + cmd->length) ; 	
		}
		else 
			return 0;			
}

static int OnGetAIMode(KERNEL_MESSAGE* cmd,int usersockfd)
{
	char mode_name[120];
	read_profile_string("AI_MODE","ai_name",mode_name,sizeof(mode_name),"face-detection-adas","config.ini");
	cmd->length=strlen(mode_name);
	strcpy(cmd->data,mode_name);
	cmd->data[cmd->length]=0;
	PTRACE("return Ai mode %s",cmd->data);
	return writeblock( usersockfd , (char*)cmd , sizeof(MESSAG_HEADER) + cmd->length ) ; 		
}

static int OnDelAIMode(KERNEL_MESSAGE* cmd,int usersockfd)
{
	write_profile_string("AI_MODE","ai_name","None","config.ini");
	system("rm -f blob/vcam*");
	cmd->data[0]= 1;
	cmd->length=1;
	return writeblock( usersockfd , (char*)cmd , sizeof(MESSAG_HEADER) + cmd->length ) ; 		
}

static int OnReboot(KERNEL_MESSAGE* cmd,int usersockfd)
{
		BYTE action=cmd->data[0];
		cmd->data[0]= 1;
		cmd->length=1;			
		writeblock( usersockfd , (char*)cmd , sizeof(MESSAG_HEADER) + cmd->length ) ;		
		os_sleep(200);//write back ok then reboot	
		if (action==0)
		{
			exit(1);	
		}
		else if (action==1)
		{	
			system("reboot");
		}
		else if (action==2)
		{
			system("killall Rtsp");
			os_sleep(200);
			exit(1);	//ensure  the first frame is I frame
		}
		return 0;	
}

static int OnGetEncParam(KERNEL_MESSAGE* cmd,int usersockfd)
{
	struct enc_param enc;
	memset(&enc,0,sizeof(enc));
	enc.enc_type=read_profile_int("ENC_PARAM","enc_type",265,"config.ini");	
	enc.enc_bps=read_profile_int("ENC_PARAM","enc_bps",4000*1000,"config.ini");	
	memcpy(cmd->data,&enc,sizeof(enc));
	cmd->length=sizeof(enc);
	return writeblock( usersockfd , (char*)cmd , sizeof(MESSAG_HEADER) + cmd->length ) ; 			
}

static int OnSetEncParam(KERNEL_MESSAGE* cmd,int usersockfd)
{
	struct enc_param* enc = (struct enc_param*)cmd->data;
	char buf[50] = {0};
	sprintf(buf,"%d",enc->enc_type);
	write_profile_string("ENC_PARAM","enc_type",buf,"config.ini");
	
	memset(buf,0,sizeof(buf));
	sprintf(buf,"%d",enc->enc_bps);
	write_profile_string("ENC_PARAM","enc_bps",buf,"config.ini");
	cmd->data[0]= 1;
	cmd->length=1;
	return writeblock( usersockfd , (char*)cmd , sizeof(MESSAG_HEADER) + cmd->length ) ; 	
}

static int OnEnCrypt(KERNEL_MESSAGE* cmd,int usersockfd)
{
	Encrypt_t info;
	memset(&info,0,sizeof(Encrypt_t));
	device_control_get_device_info(&info);
	memcpy(cmd->data,&info.reserve,sizeof(info.reserve));
	cmd->length=sizeof(info.reserve);
	return writeblock( usersockfd , (char*)cmd , sizeof(MESSAG_HEADER) + cmd->length ) ; 	 		
}

/*user customed data handle,default ack 1(ok)*/
static int OnCustomed(KERNEL_MESSAGE* cmd,int usersockfd)
{
		//PTRACE("recv user customed data len=%d %s",cmd->length,cmd->data);
		cmd->data[0]= 1;
		cmd->length=1;			
		return writeblock( usersockfd , (char*)cmd , sizeof(MESSAG_HEADER) + cmd->length ) ;			
}

static struct MESSAGE_MAP msg_maps[]={
		{APP_GET_VERSION,OnGetVersion},
		{APP_HEART_TEST, OnHeartTest},

		{SYS_START_UPDATE, OnUpdateStart},
		{SYS_APP_UPDATE,   OnUpdateApp},
		{APP_GET_AI_MODE,  OnGetAIMode},
		{APP_DEL_AI_MODE,  OnDelAIMode},
		{APP_REM_REBOOT,   OnReboot},
		{APP_GET_VIDEO_PARAM, OnGetEncParam},		
		{APP_SET_VIDEO_PARAM, OnSetEncParam},	
		
		{APP_GET_ENCRYPT_PARAM, OnEnCrypt},
		{APP_IPC_CUSTOM_DATA, OnCustomed},	
};

void* ControlServ(void* param)
{
	long usersockfd = (long)param;
	socklen_t iolen;	
	fd_set rdfdset;
	struct timeval tmv;		
	struct sockaddr_in readaddr; 
	KERNEL_MESSAGE cmd; 
	pthread_detach(pthread_self());
	
	iolen = sizeof(readaddr);
	memset(&readaddr,0,iolen);
	getpeername(usersockfd,(struct sockaddr *)&readaddr,&iolen); 
	PTRACE("Start server Client %s : port %d",inet_ntoa(readaddr.sin_addr),ntohs(readaddr.sin_port));
	while(core_context->running)	
	{	
		FD_ZERO(&rdfdset);
		FD_SET(usersockfd,&rdfdset);
		memset(&cmd,0,sizeof(KERNEL_MESSAGE));
		tmv.tv_sec = 30;
		tmv.tv_usec = 0;
	
		int ret=select(usersockfd+1,&rdfdset,NULL,NULL,&tmv);
		if ( ret< 0)
		{
			 perror("select failed");
			 break;
			// continue;
		}
		else if (ret==0)	 //time out,write to clinet heart test to keep client tcp live
		{
			MESSAG_HEADER  msg;
			msg.command=APP_HEART_TEST;
			msg.receiver=REMOTE_CLI_MOD;
			msg.sender=CORE_APP_MOD;
			msg.length=0;		
			writeblock(usersockfd,(char*)&msg,sizeof(MESSAG_HEADER));	//only header ,no ack
			continue;
		}
		
		if (FD_ISSET(usersockfd,&rdfdset))
		{		
			iolen = readblock(usersockfd,(char*)&cmd,sizeof(MESSAG_HEADER));			
			if (iolen <= 0)
			{
				PTRACE("client close the connection or read client data error in control service!errno=%d",errno); 							
				break;
			}		
			
			bool bvalid=true;
			if ((cmd.command&0xff0000) != APP_SYSCTRL_MSG)
			{
				PTRACE("comand  header 0x%6x  error",cmd.command&0xff0000);
				bvalid=false;
			}
			
			if (SYS_APP_UPDATE==cmd.command)
			{
					iolen = readblock(usersockfd,up_buffer,cmd.length);	
					 if (iolen<=0)
					 {
					 		PTRACE("client close the connection or read client data error in service control command!errno=%d",errno); 							
							break;	
					 }			
					 OnUpdateApp(&cmd, usersockfd);
					 continue;	
			}
			else
			{
				if ((cmd.length>0)&&(cmd.length>sizeof(cmd.data)))
				{
					PTRACE("too long for buffer %d",cmd.length);
					bvalid=false;
				}
				if (!bvalid)
				{
						PTRACE("invalid  command 0x%6x length=%d recvied! closed!",cmd.command,cmd.length);
						//continue;
						break; //stop server this client
				}		
				if (cmd.length>0)
				{
					 iolen = readblock(usersockfd,cmd.data,cmd.length);	
					 if (iolen<=0)
					 {
					 		PTRACE("client close the connection or read client data error in service control command!errno=%d",errno); 							
							break;	
					 }
				}
			}
		}
		else  //invalid read
					continue;

	  PTRACE("receive msg = 0x%6x,len=%d from %d",cmd.command,cmd.length,cmd.sender);   
    SWAP(cmd.sender,cmd.receiver);
    
		int i=0;
		for ( i=0;i<ARRAYSIZE(msg_maps);i++)
		{
				if (msg_maps[i].message==cmd.command )
				{
					 int ret=msg_maps[i].msg_handle(&cmd,usersockfd);
					 if (ret<0)
					 		PTRACE("handle error for command=%d",cmd.command);
					 break;
				}
		}
		if  (i==ARRAYSIZE(msg_maps))
			PTRACE("Not support this command=0x%6x yet!",cmd.command);				
	}
	
	close(usersockfd);
	PTRACE("Close client %s:%d",inet_ntoa(readaddr.sin_addr),ntohs(readaddr.sin_port));	
	{
		std::lock_guard<std::mutex> lg(m_mutex);
		LISTFD::iterator it;  
		for (it = clientfds.begin(); it != clientfds.end(); it++) 
		{
			if (*it==usersockfd)
				it=clientfds.erase(it);
		}
	}
	return NULL;
}

void*  remote_ctrl_loop( void *arg)
{
	int sockfd,newsockfd;
	int addr_len;
	struct sockaddr_in addr ;
	struct sockaddr_in  cliaddr; 
	
	pthread_detach(pthread_self());
	int val = 1;
	addr_len = sizeof(struct sockaddr);
	addr.sin_family      = AF_INET       ;
	addr.sin_addr.s_addr = htonl ( INADDR_ANY ) ;
	addr.sin_port        = htons ( REMOTE_PORT) ;
	
	sockfd  = socket( AF_INET, SOCK_STREAM, 0 );
	setsockopt( sockfd , SOL_SOCKET , SO_REUSEADDR , &val , sizeof(int) ) ;
	if( bind  ( sockfd , ( struct sockaddr *)&addr , addr_len ) < 0 )
	{
	        PTRACE("start_network: Bind TCP PORT[%d] Error ." , REMOTE_PORT ) ;
	        close(sockfd);
	        //return NULL;
	        exit(-1);
  }
 
  if(listen(sockfd,5)>0) 
	{
		perror("failed to listen");
		close(sockfd);		
		//return NULL;
		exit(-1);
	}	
	PTRACE("start_network: Bind TCP PORT[%d] OK ." , REMOTE_PORT  ) ;
	
	while(core_context->running)
	{
		/* accept the next connection */ 
		pthread_t childthrd;
		socklen_t clilen = sizeof(cliaddr); 
		newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen); 
		if (newsockfd < 0 && errno == EINTR) continue; 
		/* a signal might interrupt our accept() call */ 
		else if (newsockfd < 0) //if close sockfd ,bring this action
		{
			/* something quite amiss -- kill the server */ 
			perror("failed to accept connection");
			//break;
			continue;
		}		
		
		PTRACE("Accept client:%s:%d",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));	
		if(pthread_create(&childthrd,NULL,ControlServ,(void*)newsockfd) != 0)
		{
			PTRACE("failed to create control service  thread! \n");	
		}				
		else //success 
		{
				std::lock_guard<std::mutex> lg(m_mutex);
				clientfds.push_back(newsockfd);
		}
  }
  PTRACE("*****exit thread %s*****",__FUNCTION__);
  return NULL;
}

