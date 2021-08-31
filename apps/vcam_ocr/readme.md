# Introduction

It is an OCR example from Baidu Paddle-Lite used vcam which is run on Raspberry Pi 4 only.

| Directory                           | Content                            |
| ----------------------------------- | ---------------------------------- |
| mainApp                             | Source code to display AI results. |
| inference_lite_lib.armlinux.armv7hf | Source code to process AI results. |
| bin                                 | Example to run OCR model.          |
| public                              | Library of source code.            |



# Running Step

1. Step  mainApp 

- Install opencv 3
```
sudo apt-get install libopencv-dev
```

- Install libusb1.0
```
sudo apt-get install libusb-1.0-0-dev
```


- Compile in `vcam_ocr/mainApp`
```
sudo make clean
sudo make
```

- Run in `vcam_ocr/mainApp/bin`
```
sudo ./mainApp
```

2. Step  Paddle CRNN Text Recognition Algorithm

```
cd vcam_ocr/inference_lite_lib.armlinux.armv7hf/demo/cxx/ocr`
sudo make
cd vcam_ocr/inference_lite_lib.armlinux.armv7hf/demo/cxx/ocr/debug
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/.../ncc_ocr/inference_lite_lib.armlinux.armv7hf/demo/cxx/ocr/debug
./ocr_db_crnn
```

3. Run Bin
```
cd vcam_ocr/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/.../bin
./run.sh
```

4. Train model

Training tool running on x86 system for paddle OCR models may help to train model by yourself.
Please refer to ***PaddleOCR  Model training/evaluation*** [GitHub](https://github.com/PaddlePaddle/PaddleOCR/blob/release/1.1/doc/doc_en/detection_en.md) for specific usage method.

  

