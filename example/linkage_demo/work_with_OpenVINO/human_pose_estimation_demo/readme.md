# Human Pose Estimation
This demo showcases the work of multi-person 2D pose estimation algorithm. The task is to predict a pose: body skeleton, which consists of keypoints and connections between them, for every person in an input video. The pose may contain up to 18 keypoints: *ears, eyes, nose, neck, shoulders, elbows, wrists, hips, knees*, and *ankles*. Some of potential use cases of the algorithm are action recognition and behavior understanding. You can use the following pre-trained model with the demo:

- `human-pose-estimation-0001`, which is a human pose estimation network, that produces two feature vectors. The algorithm uses these feature vectors to predict human poses.

<img src="human-pose-estimation-0001.png" height="60%" width="60%">

## Specification
| Metric                 | Value  |
| ---------------------- | ------ |
| Average Precision (AP) | 42.8%  |
| GFlops                 | 15.435 |
| MParams                | 4.099  |
| Source framework       | Caffe* |

Average Precision metric described in [COCO Keypoint Evaluation site](http://cocodataset.org/#keypoints-eval).

## Performance

## Inputs
Name: `input` , shape: [1x3x256x456]. An input image in the [BxCxHxW] format, where:
     - B - batch size
     - C - number of channels
     - H - image height
     - W - image width.
     Expected color order is BGR.

## Outputs
The net outputs two blobs with the [1, 38, 32, 57] and [1, 19, 32, 57] shapes. The first blob contains keypoint pairwise relations (part affinity fields), while the second blob contains keypoint heatmaps.

## Usage

- Setup
```
rm -r /opt/intel/openvino/inference_engine/demos
sudo cp -a /.../vcam/ncc_cdk/Samples/Demo/work _with_OpenVINO/human_pose_estimation_demo  /opt/intel/openvino/inference_engine/demos/
```
- Compile
```
cd /opt/intel/openvino/inference_engine/demos/
sudo ./build_samples.sh
```
- Check Result
```
enter ~/omz_demos_build/intel64/Release
Look for `human_pose_estimation_demo` if compile succeeded
```
- Setup Environment
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
-  Execution
``` 
cd ~/omz_demos_build/intel64/Release/
./human_pose_estimation_demo -i cam -m ../module/human-pose-estimation-0001.xml -d MYRIAD
```
