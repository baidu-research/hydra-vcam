# How to  

If you want to quickly learn to use VCAM camera to run the model and view the results, you can use [VCAM Viewer](../../apps/vcam_viewer) directly.
However, if you want to use our framework to get the video stream and run the model, and then connect your own project, it is recommended that you start with the following demos.



* [Capture video](./capture_video)	

  The first step of secondary development based on VCAM camera is to let the camera flow out. If you need to run the model, the video stream will be used as input to the model. Only when the video stream is correct can the basis of AI operation be guaranteed, so this step is very important.

  The test initialization creates 3 threads to process YUV/H26X and mjpeg, respectively. Yuv uses OpenCV to display directly, and a Mjpeg picture is saved in locally. At the same time, a h26x image will be saved locally and can be played by ffplay.

  

* [Load a model](./load_a_model)  & [Multiple_models](./multiple_models)
  
  When you want your algorithm to do some simple things, such as classifying, detecting and segmenting these characters, you may only need a model for reasoning. If your needs are complex, such as character recognition, face recognition and direction recognition, you need more than two models to complete the task. At present, VCAM supports two-stage series model at most.
  
  This Demo load and run the model, which is usually used to verify model compatibility.
  



* [how to use sdk](./how_to_use_sdk)

  This demo includes camera parameter configuration, model parameter configuration, configuration loading, obtaining video stream and AI operation results, analyzing and displaying the results, and the whole process. Learn this demo to fully understand VCAM SDK, which will help you better complete secondary development.
