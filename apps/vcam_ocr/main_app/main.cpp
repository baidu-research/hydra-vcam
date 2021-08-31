// SPDX-License-Identifier: Apache-2.0
//
#include "common.h"

APP_CORE_CONTEXT  * core_context = NULL ;

int main(int argc ,char *argv[])
{
	core_context = (APP_CORE_CONTEXT*)malloc(sizeof(APP_CORE_CONTEXT));
	if( core_context == NULL )
	{
	    PTRACE("app_core_init , alloc memory failed .");
	    return -1 ;
	}	
	//memset(core_context,0,sizeof(APP_CORE_CONTEXT));
	
//	core_timer_init();
	core_context->running=1;	
	PTRACE("****init all device ok!*****");
	
	pthread_t nccthrd,remoterd;
	
#if  1
	if(pthread_create(&nccthrd,NULL,sys_ctrl_loop,NULL) != 0)
	{
		PTRACE("failed to create sys_ctrl_loop thread! \n");	
	}	
	os_sleep(1000);//ensure ncc run ok 
#endif
#if 0		
	if(pthread_create(&remoterd,NULL,remote_ctrl_loop,NULL) != 0)
	{
		PTRACE("failed to create remote_ctrl_loop  thread! \n");	
	}	
#endif		
	ncc_loop(NULL);	
	return 0;
}
