# How to use SDK


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
sudo ./vcam [0,1,2,3]		//4 modes
```

**Modes Selection**
```
vcam 0
//mode 0 : support one AI net example , face-detection model [default]
```

```
vcam 1
//mode 1: support Secondary model example.
//1.vehicle-license-plate-detection       2.license-plate-recognition
```

```
vcam 2
//mode 2: one ai net with 2 input.
```

```
vcam 3
//mode 3:used call back to get data from ncc device.
```

**Notes:**
we used opecv4.4 which are from openvino2020.3 version
if you used opencv3.x,just edit the makefile to select it
OPENCV = `pkg-config opencv --cflags --libs`

