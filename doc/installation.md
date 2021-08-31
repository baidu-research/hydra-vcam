# Installation

## Download

## Installation environment dependency

### Linux

- FFmpeg and libs
```
sudo apt-get update
sudo apt-get install libgl1-mesa-dev -y
sudo apt-get install unixodbc -y 
sudo apt-get install libpq-dev -y 
sudo apt-get install ffmpeg -y
sudo apt-get install libusb-dev -y
sudo apt-get install libusb-1.0.0-dev -y
```

- OpenCV
```
# 1.
sudo apt-get install build-essential
sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev
# 2.install cmake
sudo apt-get install cmake
# 3.install pkg-config
sudo apt-get install pkg-config
# 4.download opencv 3.4.0 https://github.com/opencv/opencv/archive/refs/tags/3.4.0.tar.gz
# 5.unzip 3.4.0.tar.gz
tar zxvf opencv-3.4.0.tar.gz
# 6.enter opencv-3.4.0 and mkdir build
cd opencv-3.4.0
mkdir build
# 7.cmake
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local .. 
```
Note: If encounter any problem during cmake, Please download OpenCV separately

- Setup
```
# 8.make
make
sudo make install
# 9.enter /etc/ld.so.conf.d/
cd /etc/ld.so.conf.d/
# 10.add /usr/local/lib to opencv.conf
sudo gedit opencv.conf
# 11.save and exit
sudo ldconfig
# 12.add 
# PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig 
# export PKG_CONFIG_PATH 
# to /etc/bash.bashrc
sudo gedit /etc/bash.bashrc
# 13.save and exit
# use pkg-config opencv --modversion to find opencv version
pkg-config opencv --modversion
```

### Raspberry PI

System：Raspberry Pi OS with desktop Kernel version:5.10

Board：Raspberry Pi 4B

- Libusb, OpenCV & FFmpeg
```
sudo apt-get install libopencv-dev -y
sudo apt-get install libusb-dev -y
sudo apt-get install libusb-1.0.0-dev -y
sudo apt-get install ffmpeg -y
sudo apt-get install python3-opencv -y
```

### Windows

- FFmpeg & OpenCV
```
Reference
ffmpeg url：https://pan.mebk.org/s/0WmEsM passwd：vcam
opencv url：https://pan.mebk.org/s/aqpZUg passwd：vcam
```
