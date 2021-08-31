## OpenVINO model optimizer

To deploy a deep learning model on end-point target devices, you need to optimize and convert a trained model to the VPU characteristics to  achieve higher operating performance. VCAM is compatible with  OpenVINO's tool set and model format, and needs to rely on Intel  OpenVINO's model optimizer to complete model optimization and conversion into Blob format. When using VCAM SDK, you need to install OpenVINO  as follows: If you need to convert the trained model yourself, you need to install  OpenVINO to run the model optimizer. When OpenVINO runs in a mixed mode with the OpenVINO inference engine,  it also needs OpenVINO support.



### Download and install OpenVINO

VCAM currently supports OpenVINO version: 2020.3.194, OpenVINO installation reference [here](https://docs.openvinotoolkit.org/2020.3/_docs_install_guides_installing_openvino_linux.html).



### Intel Free model download

VCAM supports OpenVINO models, Intel has a large number of free  trained models for learning reference and testing. After we have  installed OpenVINO, we can use the Intel download tool to download the  model collection. 

Model download tool path: `openvino/deployment_tools/tools/model_downloader/downloader.py`

Common commands are as follows:

* View all downloadable models：./downloader.py --print

* Download the specified model：./downloader.py --name *

  

### Model optimization and format conversion

When we need to deploy a trained model to VCAM, we need to optimize  and transform the model. After installing OpenVINO, you can use the  model optimization tool: `/opt/intel/openvino/deployment_tools/model_optimizer/mo.py` to optimize the model. For specific documents, see the official Intel documents: [Model Optimizer Developer Guide](https://docs.openvinotoolkit.org/2020.3/_docs_MO_DG_prepare_model_Config_Model_Optimizer.html)[ ](https://docs.openvinotoolkit.org/2020.3/_docs_MO_DG_prepare_model_Config_Model_Optimizer.html)

 After the model optimization is completed, the model needs to be converted to the Blob format before it can be deployed on VCAM. In the OpenVINO  installation directory: `/opt/intel/openvino/deployment_tools/inference_engine/lib/intel64myriad_compile` tool.  

The method of use is as follows:   

enter from the command line terminal：
```
./myriad_compile -m  input_xxx-fp16.xml  -o output_xxx.blob  -VPU_PLATFORM VPU_2480  -VPU_NUMBER_OF_SHAVES  6  -VPU_NUMBER_OF_CMX_SLICES 6
```

  After the format conversion is completed, the model can be deployed on VCAM, refer to: `SDK/Samples/How_to/load a model`, or use the VCAM View interface program to add the model to deploy and test it.



