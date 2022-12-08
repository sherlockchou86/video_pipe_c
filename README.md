
## adapt to jetson tx2 ##

code adapted for jetson tx2 (other jetson devices also work fine).

- infer nodes based on `tensorrt` works, `./thrid_party/trt_vehicle` works too.
- infer nodes based on `paddle` does NOT work any more, `./third_party/paddle_ocr` not work either (has disabled related code).
- infer nodes based on `opencv::dnn` work as usual.


refer to [doc/env.md](doc/env.md) for more.


please disable code related to `tensorrt` for other embedding platforms other than NVIDIA.