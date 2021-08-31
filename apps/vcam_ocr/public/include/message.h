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
#ifndef  _MESSAGE_INFO_H
#define  _MESSAGE_INFO_H

#include "includes.h"

#define MAIN_CTRL_PORT     5050	
#define GUI_CTRL_PORT      5051	
#define WT_CTRL_PORT       5052	
#define RTSP_CTRL_PORT     5053
#define ONVIF_CTRL_PORT    5054

#define REMOTE_PORT        8088

typedef struct
{
    int  sender   ;      //send mode
    int  receiver ;      //receive mode
    int  command  ;      //command 
    int  length   ;      //command length
}_PACKED_ MESSAG_HEADER ;

typedef struct
{
    int  sender   ;      //send mode
    int  receiver ;      //receive mode
    int  command  ;      //command 
    int  length   ;      //command length
    char data[240] ;     //command length，deault  execute reusult:data[0]=1: ok  0: error
}_PACKED_ KERNEL_MESSAGE   ;

#define  APP_MODULE               0x8000
#define  CORE_APP_MOD             ( APP_MODULE + 0 )   //32768
#define  GUI_APP_MOD              ( APP_MODULE + 1 )
#define  RTSP_APP_MOD             ( APP_MODULE + 2 )
#define  ONVIF_APP_MOD            ( APP_MODULE + 3 )
#define  WT_APP_MOD               ( APP_MODULE + 4 )
#define  REMOTE_CLI_MOD           ( APP_MODULE + 5 )  

#define  APP_SYSCTRL_MSG          0x800000
#define  APP_GET_VERSION          APP_SYSCTRL_MSG+0   //public command for all app module
#define  APP_HEART_TEST           APP_SYSCTRL_MSG+1   //heart test
#define  APP_REM_REBOOT           APP_SYSCTRL_MSG+2   //reboot 
#define  APP_VIDEO_CONTROL        APP_SYSCTRL_MSG+3   //video control by rtsp 
#define  APP_REP_MEDIA            APP_SYSCTRL_MSG+4
#define  APP_IPC_ADDR             APP_SYSCTRL_MSG+5    
#define  APP_GET_AI_MODE          APP_SYSCTRL_MSG+6    
#define  APP_DEL_AI_MODE          APP_SYSCTRL_MSG+7   

#define  APP_GET_VIDEO_PARAM      APP_SYSCTRL_MSG+8
#define  APP_SET_VIDEO_PARAM      APP_SYSCTRL_MSG+9
#define  APP_GET_ENCRYPT_PARAM    APP_SYSCTRL_MSG+10

#define  APP_IPC_CUSTOM_DATA      APP_SYSCTRL_MSG+100

#define  APP_OCR_RES_DATA         APP_SYSCTRL_MSG+101

//
#define  SYS_CTRL_MSG             APP_SYSCTRL_MSG+1000     //0x83000e8
#define  SYS_START_UPDATE         SYS_CTRL_MSG+0      
#define  SYS_APP_UPDATE           SYS_CTRL_MSG+1      

#define  SYS_UI_HINT              SYS_CTRL_MSG+3      //gui hint info 
#define  SYS_GET_UP_MD5        		SYS_CTRL_MSG+4      //get update package md5
#define  SYS_SET_UP_MD5        		SYS_CTRL_MSG+5      //write update package file md5   

#endif

