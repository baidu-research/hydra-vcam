// Copyright (c) 2020 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "paddle_api.h" // NOLINT
#include <chrono>
#include <stdlib.h>
#include "cls_process.h"
#include "crnn_process.h"
#include "db_post_process.h"
#include "shm.h"
#include  "message.h"
#include "sysinfo.h"
#include<fstream>
#include<unistd.h>

using namespace paddle::lite_api; // NOLINT
using namespace std;

static float outptr[256*128];
//static unsigned char yuvdata[256*128*3/2];
static char rgb_buf[256*128*3];


/*void getmeteDATA(float *outptr)
{
  
  ifstream myfile("outputbgrunpacked.txt");

  for(int i=0;i<256*128;i++)
{
  myfile>>outptr[i];
}

}*/

/*void getyuvDATA(cv::Mat &bgrImg)
{
  FILE *fs;
  int len=256*128*3/2;
  fs=fopen("12.yuv","rb");
  unsigned char *pSrc=(unsigned char*)malloc(len);
  fread(pSrc,1,len,fs);
  cv::Mat yuvImg(128*3/2,256,CV_8UC1);
  memcpy(yuvImg.data,pSrc,len);
  

 cv::cvtColor(yuvImg,bgrImg,101);
 
}*/



// fill tensor with mean and scale and trans layout: nhwc -> nchw, neon speed up
void NeonMeanScale(const float *din, float *dout, int size,
                   const std::vector<float> mean,
                   const std::vector<float> scale) {
  if (mean.size() != 3 || scale.size() != 3) {
    std::cerr << "[ERROR] mean or scale size must equal to 3\n";
    exit(1);
  }
  float32x4_t vmean0 = vdupq_n_f32(mean[0]);
  float32x4_t vmean1 = vdupq_n_f32(mean[1]);
  float32x4_t vmean2 = vdupq_n_f32(mean[2]);
  float32x4_t vscale0 = vdupq_n_f32(scale[0]);
  float32x4_t vscale1 = vdupq_n_f32(scale[1]);
  float32x4_t vscale2 = vdupq_n_f32(scale[2]);

  float *dout_c0 = dout;
  float *dout_c1 = dout + size;
  float *dout_c2 = dout + size * 2;

  int i = 0;
  for (; i < size - 3; i += 4) {
    float32x4x3_t vin3 = vld3q_f32(din);
    float32x4_t vsub0 = vsubq_f32(vin3.val[0], vmean0);
    float32x4_t vsub1 = vsubq_f32(vin3.val[1], vmean1);
    float32x4_t vsub2 = vsubq_f32(vin3.val[2], vmean2);
    float32x4_t vs0 = vmulq_f32(vsub0, vscale0);
    float32x4_t vs1 = vmulq_f32(vsub1, vscale1);
    float32x4_t vs2 = vmulq_f32(vsub2, vscale2);
    vst1q_f32(dout_c0, vs0);
    vst1q_f32(dout_c1, vs1);
    vst1q_f32(dout_c2, vs2);

    din += 12;
    dout_c0 += 4;
    dout_c1 += 4;
    dout_c2 += 4;
  }
  for (; i < size; i++) {
    *(dout_c0++) = (*(din++) - mean[0]) * scale[0];
    *(dout_c1++) = (*(din++) - mean[1]) * scale[1];
    *(dout_c2++) = (*(din++) - mean[2]) * scale[2];
  }
}

int64_t ShapeProdution(const shape_t& shape)
{
  int64_t res=1;
for(auto i:shape)res*=i;
return res;
}
// resize image to a size multiple of 32 which is required by the network
cv::Mat DetResizeImg(const cv::Mat img, int max_size_len,
                     std::vector<float> &ratio_hw) {
  int w = img.cols;
  int h = img.rows;

  float ratio = 1.f;
  int max_wh = w >= h ? w : h;
  if (max_wh > max_size_len) {
    if (h > w) {
      ratio = static_cast<float>(max_size_len) / static_cast<float>(h);
    } else {
      ratio = static_cast<float>(max_size_len) / static_cast<float>(w);
    }
  }

  int resize_h = static_cast<int>(float(h) * ratio);
  int resize_w = static_cast<int>(float(w) * ratio);
  if (resize_h % 32 == 0)
    resize_h = resize_h;
  else if (resize_h / 32 < 1 + 1e-5)
    resize_h = 32;
  else
    resize_h = (resize_h / 32 - 1) * 32;

  if (resize_w % 32 == 0)
    resize_w = resize_w;
  else if (resize_w / 32 < 1 + 1e-5)
    resize_w = 32;
  else
    resize_w = (resize_w / 32 - 1) * 32;

  cv::Mat resize_img;
  cv::resize(img, resize_img, cv::Size(resize_w, resize_h));

  ratio_hw.push_back(static_cast<float>(resize_h) / static_cast<float>(h));
  ratio_hw.push_back(static_cast<float>(resize_w) / static_cast<float>(w));
  return resize_img;
}

cv::Mat RunClsModel(cv::Mat img, std::shared_ptr<PaddlePredictor> predictor_cls,
                    const float thresh = 0.9) {
  std::vector<float> mean = {0.5f, 0.5f, 0.5f};
  std::vector<float> scale = {1 / 0.5f, 1 / 0.5f, 1 / 0.5f};

  cv::Mat srcimg;
  img.copyTo(srcimg);
  cv::Mat crop_img;
  img.copyTo(crop_img);
  cv::Mat resize_img;

  int index = 0;
  float wh_ratio =
      static_cast<float>(crop_img.cols) / static_cast<float>(crop_img.rows);

  resize_img = ClsResizeImg(crop_img);
  resize_img.convertTo(resize_img, CV_32FC3, 1 / 255.f);

  const float *dimg = reinterpret_cast<const float *>(resize_img.data);

  std::unique_ptr<Tensor> input_tensor0(std::move(predictor_cls->GetInput(0)));
  input_tensor0->Resize({1, 3, resize_img.rows, resize_img.cols});
  auto *data0 = input_tensor0->mutable_data<float>();

  NeonMeanScale(dimg, data0, resize_img.rows * resize_img.cols, mean, scale);
  // Run CLS predictor
  predictor_cls->Run();

  // Get output and run postprocess
  std::unique_ptr<const Tensor> softmax_out(
      std::move(predictor_cls->GetOutput(0)));
  std::unique_ptr<const Tensor> label_out(
      std::move(predictor_cls->GetOutput(1)));
  auto *softmax_scores = softmax_out->mutable_data<float>();
  auto *label_idxs = label_out->data<int64>();
  int label_idx = label_idxs[0];
  float score = softmax_scores[label_idx];

  if (label_idx % 2 == 1 && score > thresh) {
    cv::rotate(srcimg, srcimg, 1);
  }
  return srcimg;
}

void RunRecModel(std::vector<std::vector<std::vector<int>>> boxes, cv::Mat img,
                 std::shared_ptr<PaddlePredictor> predictor_crnn,
                 std::vector<std::string> &rec_text,
                 std::vector<float> &rec_text_score,
                 std::vector<std::string> charactor_dict,
                 std::shared_ptr<PaddlePredictor> predictor_cls,
                 int use_direction_classify) {
  std::vector<float> mean = {0.5f, 0.5f, 0.5f};
  std::vector<float> scale = {1 / 0.5f, 1 / 0.5f, 1 / 0.5f};

  cv::Mat srcimg;
  img.copyTo(srcimg);
  cv::Mat crop_img;
  cv::Mat resize_img;

  int index = 0;
  for (int i = boxes.size() - 1; i >= 0; i--) {
    crop_img = GetRotateCropImage(srcimg, boxes[i]);
    if (use_direction_classify >= 1) {
      crop_img = RunClsModel(crop_img, predictor_cls);
    }
    float wh_ratio =
        static_cast<float>(crop_img.cols) / static_cast<float>(crop_img.rows);

    resize_img = CrnnResizeImg(crop_img, wh_ratio);
    resize_img.convertTo(resize_img, CV_32FC3, 1 / 255.f);

    const float *dimg = reinterpret_cast<const float *>(resize_img.data);

    std::unique_ptr<Tensor> input_tensor0(
        std::move(predictor_crnn->GetInput(0)));
    input_tensor0->Resize({1, 3, resize_img.rows, resize_img.cols});
    auto *data0 = input_tensor0->mutable_data<float>();

    NeonMeanScale(dimg, data0, resize_img.rows * resize_img.cols, mean, scale);
    //// Run CRNN predictor
    predictor_crnn->Run();

    // Get output and run postprocess
    std::unique_ptr<const Tensor> output_tensor0(
        std::move(predictor_crnn->GetOutput(0)));
    auto *rec_idx = output_tensor0->data<int64>();

    auto rec_idx_lod = output_tensor0->lod();
    auto shape_out = output_tensor0->shape();

    std::vector<int> pred_idx;
    for (int n = static_cast<int>(rec_idx_lod[0][0]);
         n < static_cast<int>(rec_idx_lod[0][1]); n += 1) {
      pred_idx.push_back(static_cast<int>(rec_idx[n]));
    }

    if (pred_idx.size() < 1e-3)
      continue;

    index += 1;
    std::string pred_txt = "";
    for (int n = 0; n < pred_idx.size(); n++) {
      pred_txt += charactor_dict[pred_idx[n]];
    }
    rec_text.push_back(pred_txt);

    ////get score
    std::unique_ptr<const Tensor> output_tensor1(
        std::move(predictor_crnn->GetOutput(1)));
    auto *predict_batch = output_tensor1->data<float>();
    auto predict_shape = output_tensor1->shape();

    auto predict_lod = output_tensor1->lod();

    int blank = predict_shape[1];
    float score = 0.f;
    int count = 0;

    for (int n = predict_lod[0][0]; n < predict_lod[0][1] - 1; n++) {
      int argmax_idx =
          static_cast<int>(Argmax(&predict_batch[n * predict_shape[1]],
                                  &predict_batch[(n + 1) * predict_shape[1]]));
      float max_value =
          float(*std::max_element(&predict_batch[n * predict_shape[1]],
                                  &predict_batch[(n + 1) * predict_shape[1]]));

      if (blank - 1 - argmax_idx > 1e-5) {
        score += max_value;
        count += 1;
      }
    }
    score /= count;
    rec_text_score.push_back(score);
  }
}

std::vector<std::vector<std::vector<int>>>
RunDetModel(float *outptr,cv::Mat img,
            std::map<std::string, double> Config) {
  // Read img
  int max_side_len = int(Config["max_side_len"]);

  cv::Mat srcimg;
  img.copyTo(srcimg);

  std::vector<float> ratio_hw;

  img = DetResizeImg(img, max_side_len, ratio_hw);
 /* cv::Mat img_fp;
  img.convertTo(img_fp, CV_32FC3, 1.0 / 255.f);

  // Prepare input data from image
  std::unique_ptr<Tensor> input_tensor0(std::move(predictor->GetInput(0)));
  input_tensor0->Resize({1, 3, img_fp.rows, img_fp.cols});
  auto *data0 = input_tensor0->mutable_data<float>();

  std::vector<float> mean = {0.485f, 0.456f, 0.406f};
  std::vector<float> scale = {1 / 0.229f, 1 / 0.224f, 1 / 0.225f};
  const float *dimg = reinterpret_cast<const float *>(img_fp.data);
  NeonMeanScale(dimg, data0, img_fp.rows * img_fp.cols, mean, scale);*/

  // Run predictor
  //predictor->Run();

  // Get output and post process
  //std::unique_ptr<const Tensor> output_tensor(
 //    std::move(predictor->GetOutput(0)));
  
  //printf("7729 = %2.6f\n",outptr[7729]); 
 
  // Save output
  float pred[256* 128];
  unsigned char cbuf[256* 128];

  for (int i = 0; i < int(256* 128); i++) {
    pred[i] = static_cast<float>(outptr[i]);
    cbuf[i] = static_cast<unsigned char>((outptr[i]) * 255);       
  }

  cv::Mat cbuf_map(128, 256, CV_8UC1,
                   reinterpret_cast<unsigned char *>(cbuf));
  cv::Mat pred_map(128, 256, CV_32F,
                   reinterpret_cast<float *>(pred));

  const double threshold = double(Config["det_db_thresh"]) * 255;
  const double maxvalue = 255;
  cv::Mat bit_map;
  cv::threshold(cbuf_map, bit_map, threshold, maxvalue, cv::THRESH_BINARY);
  cv::Mat dilation_map;
  cv::Mat dila_ele = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2));
  cv::dilate(bit_map, dilation_map, dila_ele);
  auto boxes = BoxesFromBitmap(pred_map, dilation_map, Config);

  std::vector<std::vector<std::vector<int>>> filter_boxes =
      FilterTagDetRes(boxes, ratio_hw[0], ratio_hw[1], srcimg);

  return filter_boxes;
}

std::shared_ptr<PaddlePredictor> loadModel(std::string model_file) {
  MobileConfig config;
  config.set_model_from_file(model_file);

  std::shared_ptr<PaddlePredictor> predictor =
      CreatePaddlePredictor<MobileConfig>(config);
  return predictor;
}

/*cv::Mat Visualization(cv::Mat srcimg,
                      std::vector<std::vector<std::vector<int>>> boxes) {
  cv::Point rook_points[boxes.size()][4];
  for (int n = 0; n < boxes.size(); n++) {
    for (int m = 0; m < boxes[0].size(); m++) {
      rook_points[n][m] = cv::Point(static_cast<int>(boxes[n][m][0]),
                                    static_cast<int>(boxes[n][m][1]));
                                    
      printf("point %d (%d,%d)\n",n,rook_points[n][m].x,rook_points[n][m].y);
    }
  }
  cv::Mat img_vis;
  srcimg.copyTo(img_vis);
  for (int n = 0; n < boxes.size(); n++) {
    const cv::Point *ppt[1] = {rook_points[n]};
    int npt[] = {4};
    cv::polylines(img_vis, ppt, npt, 1, 1, CV_RGB(0, 255, 0), 2, 8, 0);
  }

 // cv::imwrite("./vis.jpg", img_vis);
  std::cout << "The detection visualized image saved in ./vis.jpg" << std::endl;
  return img_vis;
}
*/
std::vector<std::string> split(const std::string &str,
                               const std::string &delim) {
  std::vector<std::string> res;
  if ("" == str)
    return res;
  char *strs = new char[str.length() + 1];
  std::strcpy(strs, str.c_str());

  char *d = new char[delim.length() + 1];
  std::strcpy(d, delim.c_str());

  char *p = std::strtok(strs, d);
  while (p) {
    string s = p;
    res.push_back(s);
    p = std::strtok(NULL, d);
  }

  return res;
}

std::map<std::string, double> LoadConfigTxt(std::string config_path) {
  auto config = ReadDict(config_path);

  std::map<std::string, double> dict;
  for (int i = 0; i < config.size(); i++) {
    std::vector<std::string> res = split(config[i], " ");
    dict[res[0]] = stod(res[1]);
  }
  return dict;
}

static int set_ocr_msg(const char* ocr,int size)
{
  KERNEL_MESSAGE msg;

  msg.command = APP_OCR_RES_DATA;
  msg.receiver=CORE_APP_MOD;
  msg.sender=GUI_APP_MOD;
  memcpy(msg.data,ocr,size);
  msg.length=size;
  int ret = send_recv_timeout((char*)&msg, sizeof(MESSAG_HEADER) + msg.length,MAIN_CTRL_PORT,
													  (char*)&msg,sizeof(msg),2);														
  if (ret<0)
	  return -1;
  PTRACE("set ocr %s ret=%d",ocr,ret);
  return 	(msg.data[0]=1)?0:-1;											
}

int main(int argc, char **argv) 
{
	long prev_sec=0; 
	int ocr_fps=0;
	int show_fps=0;
		
	SHARE_MEM_HANDLE  m_ocrIMGMem = shr_open(OCR_IMG_KEY,256*128*3,BLOCK_NUM);		
	if (m_ocrIMGMem==0)
	{
	  printf("open m_ocrIMGMem share memory error!\n");	
	  return NULL;
	}	 	 
	
	SHARE_MEM_HANDLE m_metaMem = shr_open(META_DATA_KEY,sizeof(outptr),BLOCK_NUM);		
	if (m_metaMem==0)
	{
	  printf("open m_metaMem share memory error!\n");	
	  return NULL;
	}	
	
 	SHARE_MEM_HANDLE m_ocrResMem = shr_open(OCR_RES_KEY,sizeof(Ocr_Items),BLOCK_NUM);		
 	if (m_ocrResMem==0)
 	{
 		PTRACE("open m_ocrResMem memory error!");	
 		return NULL;
 	}	 	  	  
 	
  //std::string det_model_file = argv[1];
  std::string rec_model_file = "ch_ppocr_mobile_v1.1_rec_infer.nb";
  std::string cls_model_file = "ch_ppocr_mobile_v1.1_cls_opt.nb";
  //std::string img_path = argv[3];
  std::string dict_path = "ppocr_keys_v1.txt";

  //// load config from txt file
  auto Config = LoadConfigTxt("./config.txt");
  int use_direction_classify = int(Config["use_direction_classify"]);

//auto det_predictor = loadModel(det_model_file);
  auto rec_predictor = loadModel(rec_model_file);
  auto cls_predictor = loadModel(cls_model_file);

  auto charactor_dict = ReadDict(dict_path);
  charactor_dict.push_back(" ");
  int ret;
    
  cv::Mat srcimg;
  srcimg.create(128,256,CV_8UC3); 
  Ocr_Items ocr_res;

	while(1)
	{
  		ret=shr_read(m_metaMem,outptr,sizeof(outptr));
		  if (ret<0)
		  {
			  // printf("read m_metaMem  empty!\n ");
		  	 usleep(10);
		  	 continue;
		  } 
    //  printf("meta %f \n",outptr[0]);
		  ret=shr_read(m_ocrIMGMem,rgb_buf,sizeof(rgb_buf));
		  if (ret<0)
		  {
			   printf("read m_ocrIMGMem  empty!\n");
		  }
    //  int bgrv;
    //  memcpy(&bgrv,rgb_buf,sizeof(int));
    //  printf("rgb %d \n",bgrv);
		  srcimg.data=(unsigned char*)rgb_buf;
  //getmeteDATA(outptr);
  //cv::Mat srcimg;
  //srcimg.create(128,256,CV_8UC1);

  //getyuvDATA(srcimg);
 
	  auto boxes = RunDetModel(outptr,srcimg, Config);
	
	  std::vector<std::string> rec_text;
	  std::vector<float> rec_text_score;
	  auto start = std::chrono::system_clock::now();
	
	  RunRecModel(boxes, srcimg, rec_predictor, rec_text, rec_text_score,
	              charactor_dict, cls_predictor, use_direction_classify);
	
	  auto end = std::chrono::system_clock::now();
	  auto duration =
	      std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  //// visualization
 // auto img_vis = Visualization(srcimg, boxes);
  
  //// print recognized text
  
  		int i=0;
			int count=rec_text.size();
			
    //	std::cout << "box size:" << boxes.size() << " text size:" << rec_text.size()<< std::endl;
      PTRACE("box size:%d text size:%d", boxes.size(),rec_text.size());  
 			ocr_fps++;
 			
 			struct  timeval tv;
			gettimeofday(&tv,NULL);									
			if (tv.tv_sec!=prev_sec)
			{
				prev_sec = tv.tv_sec;
				show_fps = ocr_fps;
				ocr_fps = 0;
			}		
			
		std::vector<std::vector<std::vector<int>>> good_boxes;	
		std::vector<std::string> good_rec_text;
	        std::vector<float> good_rec_text_score;
		
		if (count>MAX_OCR_NUMS) count=MAX_OCR_NUMS;
		
		for (  i = 0; i < count; i++)
		{
		const char* constc=nullptr;	         	
	          constc=rec_text[count-i-1].c_str();
		  #if 1

		    int EN=0;
		    int len=strlen(constc);
		   // printf("len is %d\n",len);
		    for(int bit=0;bit<=len;bit++)
		    {
		      //if(constc[bit]!=NULL&&('0'>constc[bit]||(constc[bit]>'9'&&constc[bit]<'A')||(constc[bit]>'Z'&&constc[bit]<'a')||'z'<constc[bit]))
		      if(constc[bit]>=0x81&&constc[bit]<=0xFE&&constc[bit+1]>=0x40&&constc[bit+1]<=0xFE)
		      {
			EN=0;
			break;
		      }
		      else if(constc[bit]==NULL)
			{
			  EN=1;			  
			}
		    }
		    
	            if(EN==0)
		      continue;
	      #endif
		      good_boxes.push_back(boxes[i]);
		      good_rec_text.push_back(rec_text[count-i-1]);
		      good_rec_text_score.push_back(rec_text_score[count-i-1]);
	      
	      
	      
		      }
			
			           	
		      count=good_rec_text.size();
				
		  cv::Point rook_points[good_boxes.size()][4];
	  	for (int n = 0; n < good_boxes.size(); n++) 
	  	{
	    	for (int m = 0; m < good_boxes[0].size(); m++)
	    	{
		      rook_points[n][m] = cv::Point(static_cast<int>(good_boxes[n][m][0]),
		                                    static_cast<int>(good_boxes[n][m][1]));	  
		    //  PTRACE("n:%d m:%d point(%d,%d)\n",n,m,rook_points[n][m].x,rook_points[n][m].y);                                  
	    	}
	  	}
	  		
	    for (  i = 0; i < count; i++)
	    {    	
	      
	      std::cout << i << "\t" << good_rec_text[i] << "\t" << good_rec_text_score[i] << std::endl;

    	  	
				strncpy(ocr_res.item[i].ocr,good_rec_text[i].c_str(),MAX_OCR_STR_SIZE);
				ocr_res.item[i].score=good_rec_text_score[i];
				
				for (int k=0;k<4;k++)
				{
	      	ocr_res.item[i].box.x[k]=rook_points[i][k].x;
	      	ocr_res.item[i].box.y[k]=rook_points[i][k].y;
	    	//	PTRACE("%d box :%d,%d",i,ocr_res.item[i].box.x[k],ocr_res.item[i].box.y[k]);
	    	}
  		}
  		
      if (count>0)
      {
      	ocr_res.num=count;
      	ocr_res.fps = show_fps;
       //set_ocr_msg(str_tmp,len);
	//printf("write ocr str:%s len=%d \n",str_tmp,len);
					ret=shr_write(m_ocrResMem,&ocr_res,sizeof(Ocr_Items));	
      }    
	  //sleep(1);
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
  return 0;
} 




