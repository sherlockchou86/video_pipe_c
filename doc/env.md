

## personal environment ##
---------
VS Code + Ubuntu 18.04 C++17  gcc 7.5

---------
apt-get install ffmpeg/gstreamer/other dependency.

install opencv 4 from GitHub, with ffmpeg/gstreamer ON (cuda optional).

opencv 4.6.0 cmake command:

cmake -D CMAKE_BUILD_TYPE=RELEASE \
-D CMAKE_INSTALL_PREFIX=/usr/local \
-D WITH_TBB=ON \
-D ENABLE_FAST_MATH=1 \
-D CUDA_FAST_MATH=1 \
-D WITH_CUBLAS=1 \
-D WITH_CUDA=ON \
-D BUILD_opencv_cudacodec=OFF \
-D WITH_CUDNN=ON \
-D OPENCV_DNN_CUDA=ON \
-D CUDA_ARCH_BIN=6.1 \
-D WITH_V4L=ON \
-D WITH_QT=OFF \
-D WITH_OPENGL=ON \
-D WITH_GSTREAMER=ON \
-D OPENCV_GENERATE_PKGCONFIG=ON \
-D OPENCV_PC_FILE_NAME=opencv.pc \
-D OPENCV_ENABLE_NONFREE=ON \
-D OPENCV_EXTRA_MODULES_PATH=/windows2/zhzhi/opencv_contrib-4.6.0/modules \
-D INSTALL_PYTHON_EXAMPLES=OFF \
-D INSTALL_C_EXAMPLES=OFF \
-D BUILD_EXAMPLES=OFF ..

---------
VcXsrv for screen display from WSL1 to local pc (or from remote machine to local desktop)
install: https://sourceforge.net/p/vcxsrv/wiki/Home/

export DISPLAY=local_ip:0.0 (or add to ~/.bashrc)

---------
maybe you need install a nginx as rtmp server for debug purpose. 

Also, maybe you need rtsp server to receive its stream for debug purpose.

## tips ##
use shared_ptr/make_shared in whole project, do not use new/delete.

the pipe is driven by stream data, if your app is not responding, maybe no stream input.

## git tips ##
if `git push --set-upstream origin new_branch` fails when pushing new local branch to remote, 
try run `git remote add origin https://github.com/sherlockchou86/video_pipe_c.git` first.

## about Hardware Acceleration ##
since decode & encode in VideoPipe depend on gstreamer (encapsulated inside opencv), if you want to use your GPUs/NPUs to accelerate decoding and encoding performace, you need get/install HARD decode or HARD encode gstreamer plugins correctly first and modify gst launch string (take `vp_file_des_node` for example):
```cpp
appsrc ! videoconvert ! x264enc bitrate=%d ! mp4mux ! filesink location=%s
```
to
```
appsrc ! videoconvert ! nvh264enc bitrate=%d ! mp4mux ! filesink location=%s
```
the plugin `x264enc` use CPUs to encode video stream, but `nvh264enc` use GPUs instread. if you use other platforms other than NVIDIA, you need Corresponding Hardware Acceleration plugins.

**soft/hard decode example**
```
gst-launch-1.0 filesrc location=./face.mp4 ! qtdemux ! h264parse ! avdec_h264 ! videoconvert ! autovideosink    // decode by avdec_h264 use CPUs
gst-launch-1.0 filesrc location=./face.mp4 ! qtdemux ! h264parse ! nvv4l2decoder ! videoconvert ! autovideosink // decode by nvv4l2decoder use NVIDIA GPUs
```

**soft/hard encode example**
```
gst-launch-1.0 filesrc location=./face.mp4 ! qtdemux ! h264parse ! avdec_h264 ! x264enc ! h264parse ! flvmux ! filesink location=./new_face.flv    // encode by x264enc use CPUs
gst-launch-1.0 filesrc location=./face.mp4 ! qtdemux ! h264parse ! avdec_h264 ! nvh264enc ! h264parse ! flvmux ! filesink location=./new_face.flv  // encode by nvh264enc use NVIDIA GPUs
```
[source code of hard decode/encode gstreamer plugins for NVIDIA](https://gitlab.freedesktop.org/gstreamer/gstreamer/-/tree/main/subprojects/gst-plugins-bad/sys/nvcodec).
