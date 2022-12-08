

## personal environment ##
---------
VS Code + Ubuntu 18.04 aarch64 C++17  gcc 7.5
jetson_tx2 with jetpack 4.6.2 installed (other jetson serials maybe works too)

---------
apt-get install ffmpeg/gstreamer/other dependency.

install opencv 4 from GitHub, with ffmpeg/gstreamer ON (cuda optional).

opencv 4.6.0 cmake command:

cmake -D CMAKE_BUILD_TYPE=RELEASE \
-D CMAKE_INSTALL_PREFIX=/usr/local2 \   # custom path
-D WITH_TBB=ON \
-D ENABLE_FAST_MATH=1 \
-D CUDA_FAST_MATH=1 \
-D WITH_CUBLAS=1 \
-D WITH_CUDA=ON \
-D BUILD_opencv_cudacodec=OFF \
-D WITH_CUDNN=ON \
-D OPENCV_DNN_CUDA=ON \
-D CUDA_ARCH_BIN=6.2 \    # for tx2
-D WITH_V4L=ON \
-D WITH_QT=OFF \
-D WITH_OPENGL=ON \
-D WITH_GSTREAMER=ON \
-D OPENCV_GENERATE_PKGCONFIG=ON \
-D OPENCV_PC_FILE_NAME=opencv.pc \
-D OPENCV_ENABLE_NONFREE=ON \
-D OPENCV_EXTRA_MODULES_PATH=/home/zhzhi/opencv_contrib-4.6.0/modules \
-D INSTALL_PYTHON_EXAMPLES=OFF \
-D INSTALL_C_EXAMPLES=OFF \
-D BUILD_opencv_python2=OFF \
-D BUILD_opencv_python3=OFF \
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

## how to check types of jetson device?
https://forums.developer.nvidia.com/t/how-to-determine-which-jetson-type-is/123586/5

## how to check cuda ability for jetson?
https://developer.nvidia.com/cuda-gpus

## how to check version of jetpack(from which cuda/tenssort versions)?
install jtop via python3-pip, refer to https://github.com/rbonghi/jetson_stats

## how to locate trtexec on jetson?
https://forums.developer.nvidia.com/t/where-is-trtexec/73514

`/usr/src` by default

## how to use trtexec to convert onnx to trt engine?
https://docs.nvidia.com/deeplearning/tensorrt/developer-guide/index.html#trtexec

