// Copyright (c) 2022 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <paddle_api.h>
#include <paddle_inference_api.h>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <vector>

#include <cstring>
#include <fstream>
#include <numeric>

#include "paddleocr.h"
#include "preprocess_op.h"
#include "structure_table.h"
#include "utility.h"

using namespace paddle_infer;

namespace PaddleOCR {

class PaddleStructure : public PPOCR {
public:
  explicit PaddleStructure(std::string table_model_dir = "", std::string table_char_dict_path = "");
  ~PaddleStructure();
  std::vector<std::vector<StructurePredictResult>>
  structure(std::vector<cv::Mat>& cv_all_imgs, bool layout = false,
            bool table = true);

private:
  StructureTableRecognizer *recognizer_ = nullptr;

  void table(cv::Mat img, StructurePredictResult &structure_result,
             std::vector<double> &time_info_table,
             std::vector<double> &time_info_det,
             std::vector<double> &time_info_rec,
             std::vector<double> &time_info_cls);
  std::string
  rebuild_table(std::vector<std::string> rec_html_tags,
                std::vector<std::vector<std::vector<int>>> rec_boxes,
                std::vector<OCRPredictResult> &ocr_result);

  float iou(std::vector<std::vector<int>> &box1,
            std::vector<std::vector<int>> &box2);
  float dis(std::vector<std::vector<int>> &box1,
            std::vector<std::vector<int>> &box2);

  static bool comparison_dis(const std::vector<float> &dis1,
                             const std::vector<float> &dis2) {
    if (dis1[1] < dis2[1]) {
      return true;
    } else if (dis1[1] == dis2[1]) {
      return dis1[0] < dis2[0];
    } else {
      return false;
    }
  }

  // common config
  bool use_gpu = true;
  bool use_tensorrt = false;
  int gpu_id = 0;
  int gpu_mem = 4000;
  int cpu_threads = 10;
  bool enable_mkldnn = false;
  std::string precision = "fp32";
  bool benchmark = false;

  // table
  std::string table_model_dir = "";
  int table_max_len = 488;
  int table_batch_num = 1;
  std::string table_char_dict_path = "/windows2/zhzhi/video_pipe_c/third_party/paddle_ocr/table_structure_dict.txt";
};

} // namespace PaddleOCR