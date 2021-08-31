# Structure

The overall directory structure of VCAM is introduced as follows:

```
vcam
├── apps   // configuration file, you can select model structure and modify hyperparameters through yml file
│   ├── vcam_ocr  		 	// It is an OCR example from Baidu Paddle-Lite used vcam which is run on Raspberry Pi 4 only.
│   │   ├── mainApp  	//Source code to display AI results
│   │   ├──  Bin 					//Example to run OCR model
│   │   ├── inference_lite_lib.armlinux.armv7hf 			 //Source code to process AI results
│   │   └── public            // Library of source code
│   ├── vcam_viewer   // a software used to quickly experience the VCAM  development kit
│   │   ├── qt_package  	//QT source code
│   │   ├──linux					//Linux compiled
│   │   ├── raspberry			 //Raspberry compiled
│   │   └── windows            // WIndows compiled
├──  doc
├── example
│   ├── how_to 
│   │   ├── capture_video  				//creates 3 threads to process YUV/H26X and mjpeg
│   │	├── how_to_use_sdk					
│   │   ├── load_a_model			 //Primary model 
│   │   └── multiple_models   	// Secondary model 
│   ├── linkage_demo  	
│   │	├── work_with_AlwaysAI					//pedestrian tracking demo
│   │   ├── work_with_OpenVINO			 //human_pose_estimation and   interactive_face_detection demo
│   │   └── work_with_PaddlePaddle            //vcam_ocr dmo
├──  platform
├── sdk
│   ├── drivers 		//window usb drivers
│   ├── source 
│   │   ├──	firmware			 //vcam firmware
│   │   └── library            //  c,c++,python library on Linux,Window,Raspberry
│   │   └── model    		  //openvino 2020.3 
│   ├── tools 
```

