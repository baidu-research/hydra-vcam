# Capture Video
The test initialization creates 3 threads to process YUV/H26X and mjpeg respectively. Yuv uses opencv to display directly, and a Mjpeg picture saved locally.At the same time a h26x picture saved locally and can be played by ffplay . 


## Test
* Ubuntu18.04  
* usb3.0

**Dependencies Installation**  
```
sudo apt-get install libusb-dev  libusb-1.0-0-dev 
sudo apt-get install ffmpeg
sudo apt-get install libopencv-dev
```

**Compile to Run**
```
./build.sh
cd bin
sudo ./Capturevideo
```

