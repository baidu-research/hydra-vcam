// SPDX-License-Identifier: Apache-2.0
//
#include "common.h"
#include "sdk.h"
#include "Fp16Convert.h"
#include "cameraCtrl.h"
#include "shm.h"
#include "times.hpp"

//#define RASP
#ifdef RASP
#include <wiringPi.h>
#endif

#define OCR_WIDTH   256
#define OCR_HEIGH   128

const int  AREA_K_W = 4;
const int  AREA_K_H = 4;
const float OCR_MAX=0.7;

#include "inifile.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/highgui/highgui_c.h>
using namespace std;
using namespace cv;

static SHARE_MEM_HANDLE m_h264Mem;  //rtsp h26x data
static int cap_mode=1;   //1:h264  2:yuv420p

//ping_pong * pp=NULL;
static SingleFrame shframe;
char g_ocr_res[200];
typedef enum _ncc_status
{
	NCC_INIT=0,
	NCC_OPEN,
	NCC_PLAY,
	NCC_CLOSE
}NCC_STATUS;

static NCC_STATUS ncc_st=NCC_INIT;
Network1Par cam_info =
{
		-1,  //imageWidth
		-1,  //imageHeight                  
	    -1,  //startX
		-1,  //startY                 
		-1,   //endX
		-1,   //endY                  
		256,  //inputDimWidth
		128,   //inputDimHeight                   /* <dim>300</dim>  <dim>300</dim> */
		IMG_FORMAT_BGR_PLANAR,      //IMAGE_FORMAT   
		124,                    //meanValue
		116,
		103,
		57.5,                         //stdValue
	    1,                           /*??YUV420???????*/
	    0,                           /*??H26X??????*/
	    0,                           /*??MJPEG??????*/	  
		ENCODE_H265_MODE,            /* ???H264?????? */
		
		{0},                                    /* for 2 input param with 1 mode */
		0 ,                                  /* cascade with next AI mode*/
		1                                    /*Accelerating */
};
	
static int lowd_ncc_fw(bool breset=false)
{
	int ret=0;
	
	int enc_type=read_profile_int("ENC_PARAM","enc_type",265,"config.ini");		
	int bps=read_profile_int("ENC_PARAM","enc_bps",4000*1000,"config.ini");		
	printf("read enc_type=%d bps=%d\n",enc_type,bps);

	cam_info.mode=(enc_type==265)?ENCODE_H265_MODE:ENCODE_H264_MODE;
		
#ifdef RASP
	wiringPiSetup();
	pinMode (0, OUTPUT) ;	
	if (breset)
	{
	  digitalWrite (0, HIGH) ;
	  os_sleep(1000);	
	  digitalWrite (0,  LOW) ;
	  os_sleep(1000);	
	}		 
#endif	 
  //1. load firmware
   ret=load_fw("./moviUsbBoot","./fw/flicRefApp.mvcmd");
   if (ret<0)
   {
   		printf("lowd firmware error! return \n");
			exit(-1);
   }

   char version[100];
   get_sdk_version(version);
   printf("usb sersion:%d sdk version:%s \n",get_usb_version(),version);

 		SensorModesConfig mode[MAX_MODE_SIZE];
		int num=camera_control_get_sensorinfo(mode,MAX_MODE_SIZE);
	  for(int i=0;i<num;i++)
    {
        printf("[%d/%d]camera: %s, %dX%d@%dfps, AFmode:%d, maxEXP:%dus,gain[%d, %d]\n",i,num,
                mode[i].moduleName, mode[i].camWidth, mode[i].camHeight, mode[i].camFps,
                mode[i].AFmode, mode[i].maxEXP, mode[i].minGain, mode[i].maxGain);
    }	    

    int sensorModeId = 0; //1080P??
   // int sensorModeId = 1; //4K??
    camera_select_sensor(sensorModeId);
   // memcpy(&cameraCfg, &list.mode[sensorModeId], sizeof(cameraCfg));//select camera info

  cam_info.imageWidth  = mode[sensorModeId].camWidth;
  cam_info.imageHeight = mode[sensorModeId].camHeight; 
  cam_info.startX      = (1920-OCR_WIDTH*AREA_K_W)/2;
  cam_info.startY      = (1080-OCR_HEIGH*AREA_K_H)/2;
  cam_info.endX        = cam_info.startX + OCR_WIDTH*AREA_K_W;
  cam_info.endY        = cam_info.startY + OCR_HEIGH*AREA_K_H;
	
	char* ai_file=NULL;
	if (access(AI_BLOB_FILE,F_OK)==0)
	{
		ai_file=AI_BLOB_FILE;
	}
	ret=camera_control_set_bps(bps);
	if (ret<0)
		printf("camera_control_set_bps error ret=%d\n",ret);
		
	ai_file="blob/ocr.blob";	
	ret = sdk_init_ex(NULL,NULL, ai_file, &cam_info, sizeof(cam_info));	
  printf("sdk_init return:%d \n", ret);
	if (ret<0)
	{
		exit(-1);
	} 	
	
	ncc_st=NCC_OPEN;
	PTRACE("%s  success!",__FUNCTION__);
	return ret;
}

int open_ncc(int capmode)
{
	if (ncc_st==NCC_PLAY) return -1;
	if  (capmode == 1)  
	{
		shr_reset_size(m_h264Mem);
		camera_video_out(YUV420p,VIDEO_OUT_CONTINUOUS); 
		//camera_video_out(H26X,VIDEO_OUT_CONTINUOUS); 
	}
	else if  (capmode == 2) //vga 
	{
	}
	ncc_st=NCC_PLAY;
	cap_mode = capmode;	
	memset(g_ocr_res,0,sizeof(g_ocr_res));
	PTRACE("switch NCC_PLAY success!");
	return 0;
}

int close_ncc()
{
		if (ncc_st==NCC_CLOSE) return -1;
		ncc_st=NCC_CLOSE;
		sdk_uninit();
		cap_mode=0;
		PTRACE("%s success!",__FUNCTION__);
				
		lowd_ncc_fw();
		return 0;
}

static char rbuf[300*1024];
static char yuv420p[sizeof(frameSpecOut)+1024*1024*5];
static float fbuffer[OCR_WIDTH*OCR_HEIGH];
void*  ncc_loop( void *arg)
{
	SHARE_MEM_HANDLE m_ocrIMGMem; //video
	SHARE_MEM_HANDLE m_metaMem; //meta data
	SHARE_MEM_HANDLE m_ocrResMem;  //result	
	
	int ret;
	ncc_st=NCC_INIT;
 	m_h264Mem = shr_open(NCC_H264_KEY,sizeof(SingleFrame),BLOCK_NUM);		
 	if (m_h264Mem==0)
 	{
 		PTRACE("open share memory error!");	
 		return NULL;
 	}	 	

 	m_ocrIMGMem = shr_open(OCR_IMG_KEY,OCR_WIDTH*OCR_HEIGH*3,BLOCK_NUM);		
 	if (m_ocrIMGMem==0)
 	{
 		PTRACE("open share memory error!");	
 		return NULL;
 	}	 	 
 	
 	m_metaMem = shr_open(META_DATA_KEY,sizeof(fbuffer),BLOCK_NUM);		
 	if (m_metaMem==0)
 	{
 		PTRACE("open share memory error!");	
 		return NULL;
 	}	 	

 	m_ocrResMem = shr_open(OCR_RES_KEY,sizeof(Ocr_Items),BLOCK_NUM);		
 	if (m_ocrResMem==0)
 	{
 		PTRACE("open share memory error!");	
 		return NULL;
 	}	 
	 	
  lowd_ncc_fw(true);	
  open_ncc(1);
  
	cv::Rect box_nn;
	box_nn.x = cam_info.startX;
	box_nn.y = cam_info.startY;
	box_nn.width  = cam_info.endX - cam_info.startX;
	box_nn.height = cam_info.endY - cam_info.startY; 

	float scale = 0.5; 
	cv::Mat yuvImg;
	yuvImg.create(cam_info.imageHeight * 3/2, cam_info.imageWidth, CV_8UC1);	
				
	Ocr_Items ocr_res;			  
	bool bsave=false;
	bool bget_ocr=false;
	memset(&ocr_res,0,sizeof(Ocr_Items));
	
	while(core_context->running)	
	{	
		if (ncc_st!=NCC_PLAY)
		{
			os_sleep(100);
			continue;
		}
					
		int size= sizeof(yuv420p);
		ret=read_yuv_data(yuv420p,&size,1);
		if (ret==USB_ERROR_NO_DEVICE)
		{
			PTRACE("recv no device !%d",ncc_st);
			if (ncc_st==NCC_PLAY)
			{
				system("killall Rtsp");
				exit(1);
			}
		}				
		else if	(ret==0)
		{
			cv::Mat rgb_img;
		  
			/* YUV420P-->RGB */
			yuvImg.data = (unsigned char*)yuv420p+sizeof(frameSpecOut);
			cv::cvtColor(yuvImg, rgb_img, CV_YUV2BGR_I420);
			frameSpecOut *out = (frameSpecOut *)yuv420p;
			//PTRACE("read_yuv_data size=%d seq=%d success!",out->size,out->seqNo);
		//	continue;
		
			if (bsave)
			{
				bsave=false;
				imwrite("test.jpg",rgb_img);
			}
					
		//handle yuv
		/* �㷨��Ч���� */
			//if((out->seqNo/2)==0)
			{					
			//	CTimeUsed used("roi");
				Mat roi = rgb_img(box_nn);
				Mat ocr;
				resize(roi,ocr,Size(OCR_WIDTH,OCR_HEIGH),0,0,INTER_LINEAR);
				//cv::imshow("roi", ocr);			
				ret=shr_write(m_ocrIMGMem,ocr.data,OCR_WIDTH*OCR_HEIGH*3);																			
			}	

			cv::rectangle(rgb_img, box_nn, cv::Scalar(0,0,0xff), 2, 8, 0);
		//	if (strlen(g_ocr_res)>0)
			ret=shr_read(m_ocrResMem,&ocr_res,sizeof(Ocr_Items));
			if ((ret==0)||(bget_ocr))
			{
				bget_ocr=true;
				cv::Point origin_nn;
				cv::Rect ocr_nn;
					
				origin_nn.x = 50;
				origin_nn.y = 50;							
				int j=0;	
				for (int i=0;i<ocr_res.num;i++)
				{
					//printf("num is %d",ocr_res.num);
					if (ocr_res.item[i].score>OCR_MAX)
					{
						//origin_nn.y = 50+30*j++;	
						//cv::putText(rgb_img, ocr_res.item[i].ocr, origin_nn, cv::FONT_HERSHEY_COMPLEX, 1,  cv::Scalar(0,0,0xff), 2, 8, 0);	
						#if 0
						ocr_nn.x = box_nn.x+ocr_res.item[i].box.x[0]*AREA_K_W;
						ocr_nn.y = box_nn.y+ocr_res.item[i].box.y[0]*AREA_K_H;
						ocr_nn.width = (ocr_res.item[i].box.x[1]-ocr_res.item[i].box.x[0])*AREA_K_W;
						ocr_nn.height =(ocr_res.item[i].box.y[2]-ocr_res.item[i].box.y[1])*AREA_K_H;
						cv::rectangle(rgb_img, ocr_nn, cv::Scalar(0,0xff,0), 2, 8, 0);			
						#else
						cv::Point rook_points[ocr_res.num][4];		
						for (int k=0;k<4;k++)
						{
								rook_points[i][k].x=box_nn.x+ocr_res.item[i].box.x[k]*AREA_K_W;
								rook_points[i][k].y=box_nn.y+ocr_res.item[i].box.y[k]*AREA_K_H;
						}
						origin_nn.x = rook_points[i][0].x;
						origin_nn.y = rook_points[i][0].y-10;
						cv::putText(rgb_img, ocr_res.item[i].ocr, origin_nn, cv::FONT_HERSHEY_COMPLEX, 1,  cv::Scalar(0,0,0xff), 2, 8, 0);							
						const cv::Point *ppt[1] = {rook_points[i]};
				    int npt[] = {4};
				    cv::polylines(rgb_img, ppt, npt, 1, 1, CV_RGB(0, 255, 0), 2, 8, 0);
				    #endif	
					}			
				}																								
			}		
			
			char str_fps[100];
			sprintf(str_fps,"OCR FPS:%d",ocr_res.fps);
			cv::putText(rgb_img, str_fps, cv::Point(50,1000), cv::FONT_HERSHEY_COMPLEX, 1,  cv::Scalar(0,0xff,0), 2, 8, 0);		
							
			Mat showImage;			
			resize(rgb_img,showImage,Size(rgb_img.cols*scale,rgb_img.rows*scale),0,0,INTER_LINEAR);
			{
				cv::imshow("rgb", showImage);
				int c=cv::waitKey(1);
				  if (cv::getWindowProperty("rgb",0) ==-1)
					{cv::destroyAllWindows();
   				     break;}
				if (c=='q') break;
  		
				else if (c=='s')
				{
					bsave=true;
				}
			}					
		}		
		
#if 1	
		size=sizeof(rbuf);
		ret=read_meta_data(rbuf,&size,0);
		if (ret==0)
		{
			//	meta_relay(rbuf,size);  
				frameSpecOut *out = (frameSpecOut *)rbuf;
				uint16_t* cls_ret = (uint16_t*)(rbuf+sizeof(frameSpecOut)+OUTPUT_INDEX_SIZE);
				size -= sizeof(frameSpecOut)+OUTPUT_INDEX_SIZE;	
				size /=2;
				//printf("read read_meta_data size=%d out item size=%d success!\n",out->size,size);
				memset(fbuffer,0,sizeof(fbuffer));
				for (int i = 0; i < size; i++) 
					fbuffer[i]=f16Tof32(cls_ret[i]);	
	
				ret=shr_write(m_metaMem,fbuffer,sizeof(fbuffer));			
			//	FILE* file=fopen("meta.dat","w");
			//	fwrite(fbuffer,1,sizeof(fbuffer),file);	
			// fclose(file);	
		}		
#endif
		
#if  0		
		size=sizeof(rbuf);
		ret=read_26x_data(rbuf,&size,0);
		if (ret==0)
		{
				frameSpecOut *out = (frameSpecOut *)rbuf;		
				//PTRACE("Meta:type:%d,size:%d,seqNo:%d \n", out->type, out->size, out->seqNo);		
				shframe.length=out->size;
				uint8_t* pdata=(uint8_t*)out;
				pdata += sizeof(frameSpecOut);
												
				memcpy(shframe.frame,pdata,shframe.length);
				
				ret=shr_write(m_h264Mem,&shframe,sizeof(SingleFrame));			
				//if (ret<0)	
				//	PTRACE("shr_write 264 mem error!");
			 // else PTRACE("shr_write 264 mem  success!=%d",out->size);		
		}			
#endif								
	}    		 
	printf("exit ncc loop....\n");
	
	if (m_h264Mem>0)
	{
	  shr_close(m_h264Mem);
	  m_h264Mem=0;
  }
 
 	if (m_ocrIMGMem>0)
	{
	  shr_close(m_ocrIMGMem);
	  m_ocrIMGMem=0;
  }
 
 	if (m_metaMem>0)
	{
	  shr_close(m_metaMem);
	  m_metaMem=0;
  }

 	if (m_ocrResMem>0)
	{
	  shr_close(m_ocrResMem);
	  m_ocrResMem=0;
  }

	return NULL;
}

int  get_ncc_status()
{
		return ncc_st;
}

