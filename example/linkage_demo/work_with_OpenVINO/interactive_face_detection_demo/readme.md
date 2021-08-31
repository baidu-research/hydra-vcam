# Interactive Face Detection

## Location
```
Original file in vcam CDK: interactive_face_detection_demo
New path in OpenVINO: /opt/intel/openvino/inference_engine/demos/
```

## Build to Run
- Setup
```
cd /opt/intel/openvino/inference_engine/demos/
sudo ./build_samples.sh
if no error, you find hint like this:
Build completed, you can find binaries for all demos in the /home/dukezuo/omz_demos_build/intel64/Release subfolder.
```
- Check Result
```
cd ~/omz_demos_build/intel64/Release
if there is "interactive_face_detection_demo"，compile succeeded.
```

## Setup Environment
- Setup "module" from vcam CDK to OpenVINO
```
Original path in vcam CDK: ncc_cdk/Samples/Demo/work with OpenVINO/Debug
New path in OpenVINO: OpenVINO's run category~/omz_demos_build/intel64
```
- Copy Firmware
```
Original path in vcam CDK: ncc_cdk/Samples/Demo/work with OpenVINO/Debug
New path in OpenVINO: OpenVINO's run category~/omz_demos_build/intel64
```
-  Get USB access
```
cd ncc_cdk/Tools/deployment
sudo ./install_NCC_udev_rules.sh
```
- Restart OS

## Execution
- Enter OpenVINO
```
~/omz_demos_build/intel64/Release/
```
- Execution
```
./interactive_face_detection_demo -i cam -m ../module/face-detection-adas-0001.xml -m_ag ../module/age-gender-recognition-retail-0013.xml -m_hp ../module/head-pose-estimation-adas-0001.xml -m_em ../module/emotions-recognition-retail-0003.xml -m_lm ../module/facial-landmarks-35-adas-0002.xml -d MYRIAD
```
