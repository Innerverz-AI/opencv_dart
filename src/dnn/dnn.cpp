/*
    This file is originally from gocv project
    Licensed: Apache 2.0 license. Copyright (c) 2017-2021 The Hybrid Group.

    Modified by Rainyl.
    Licensed: Apache 2.0 license. Copyright (c) 2024 Rainyl.
*/

#include "dnn.h"
#include <string.h>
#include <vector>

CvStatus Net_Create(Net *rval)
{
  BEGIN_WRAP
  *rval = {new cv::dnn::Net()};
  END_WRAP
}
CvStatus Net_FromNet(Net net, Net *rval)
{
  BEGIN_WRAP
  *rval = {new cv::dnn::Net(*net.ptr)};
  END_WRAP
}
CvStatus Net_ReadNet(const char *model, const char *config, const char *framework, Net *rval)
{
  BEGIN_WRAP
  *rval = {new cv::dnn::Net(cv::dnn::readNet(model, config, framework))};
  END_WRAP
}
CvStatus Net_ReadNetBytes(const char *framework, VecUChar model, VecUChar config, Net *rval)
{
  BEGIN_WRAP
  *rval = {new cv::dnn::Net(cv::dnn::readNet(framework, *model.ptr, *config.ptr))};
  END_WRAP
}
CvStatus Net_ReadNetFromCaffe(const char *prototxt, const char *caffeModel, Net *rval)
{
  BEGIN_WRAP
  *rval = {new cv::dnn::Net(cv::dnn::readNetFromCaffe(prototxt, caffeModel))};
  END_WRAP
}
CvStatus Net_ReadNetFromCaffeBytes(VecUChar prototxt, VecUChar caffeModel, Net *rval)
{
  BEGIN_WRAP
  *rval = {new cv::dnn::Net(cv::dnn::readNetFromCaffe(*prototxt.ptr, *caffeModel.ptr))};
  END_WRAP
}
CvStatus Net_ReadNetFromTensorflow(const char *model, const char *config, Net *rval)
{
  BEGIN_WRAP
  *rval = {new cv::dnn::Net(cv::dnn::readNetFromTensorflow(model, config))};
  END_WRAP
}
CvStatus Net_ReadNetFromTensorflowBytes(VecUChar model, VecUChar config, Net *rval)
{
  BEGIN_WRAP
  *rval = {new cv::dnn::Net(cv::dnn::readNetFromTensorflow(*model.ptr, *config.ptr))};
  END_WRAP
}
CvStatus Net_ReadNetFromTFLite(const char *model, Net *rval)
{
  BEGIN_WRAP
  *rval = {new cv::dnn::Net(cv::dnn::readNetFromTFLite(model))};
  END_WRAP
}
CvStatus Net_ReadNetFromTFLiteBytes(VecUChar bufferModel, Net *rval)
{
  BEGIN_WRAP
  *rval = {new cv::dnn::Net(cv::dnn::readNetFromTFLite(*bufferModel.ptr))};
  END_WRAP
}
CvStatus Net_ReadNetFromTorch(const char *model, bool isBinary, bool evaluate, Net *rval)
{
  BEGIN_WRAP
  *rval = {new cv::dnn::Net(cv::dnn::readNetFromTorch(model, isBinary, evaluate))};
  END_WRAP
}
CvStatus Net_ReadNetFromONNX(const char *model, Net *rval)
{
  BEGIN_WRAP
  *rval = {new cv::dnn::Net(cv::dnn::readNetFromONNX(model))};
  END_WRAP
}
CvStatus Net_ReadNetFromONNXBytes(VecUChar model, Net *rval)
{
  BEGIN_WRAP
  *rval = {new cv::dnn::Net(cv::dnn::readNetFromONNX(*model.ptr))};
  END_WRAP
}

void Net_Close(Net *net){CVD_FREE(net)}

CvStatus Net_BlobFromImage(Mat image, Mat blob, double scalefactor, Size size, Scalar mean, bool swapRB,
                           bool crop, int ddepth)
{
  BEGIN_WRAP
  cv::Size   sz(size.width, size.height);
  cv::Scalar cm(mean.val1, mean.val2, mean.val3, mean.val4);
  cv::dnn::blobFromImage(*image.ptr, *blob.ptr, scalefactor, sz, cm, swapRB, crop, ddepth);
  END_WRAP
}

CvStatus Net_BlobFromImages(VecMat images, Mat blob, double scalefactor, Size size, Scalar mean, bool swapRB,
                            bool crop, int ddepth)
{
  BEGIN_WRAP
  cv::Size   sz(size.width, size.height);
  cv::Scalar cm = cv::Scalar(mean.val1, mean.val2, mean.val3, mean.val4);
  cv::dnn::blobFromImages(*images.ptr, *blob.ptr, scalefactor, sz, cm, swapRB, crop, ddepth);
  END_WRAP
}

CvStatus Net_ImagesFromBlob(Mat blob, VecMat *rval)
{
  BEGIN_WRAP
  auto imgs = new std::vector<cv::Mat>();
  cv::dnn::imagesFromBlob(*blob.ptr, *imgs);
  *rval = {imgs};
  END_WRAP
}

CvStatus Net_Empty(Net net, bool *rval)
{
  BEGIN_WRAP
  *rval = net.ptr->empty();
  END_WRAP
}

CvStatus Net_Dump(Net net, VecChar rval)
{
  BEGIN_WRAP
  auto ss = net.ptr->dump();
  rval.ptr = new std::vector<char>(ss.c_str(), ss.c_str() + ss.size());
  END_WRAP
}

CvStatus Net_SetInput(Net net, Mat blob, const char *name)
{
  BEGIN_WRAP
  net.ptr->setInput(*blob.ptr, name);
  END_WRAP
}

CvStatus Net_Forward(Net net, const char *outputName, Mat *rval)
{
  BEGIN_WRAP
  *rval = {new cv::Mat(net.ptr->forward(outputName))};
  END_WRAP
}

CvStatus Net_ForwardLayers(Net net, VecMat *outputBlobs, VecVecChar outBlobNames)
{
  BEGIN_WRAP
  auto blobs = new std::vector<cv::Mat>();

  std::vector<cv::String> names;
  for (int i = 0; i < outBlobNames.ptr->size(); ++i) {
    auto n = outBlobNames.ptr->at(i);
    names.push_back(cv::String(n.begin(), n.end()));
  }
  net.ptr->forward(*blobs, names);
  *outputBlobs = {blobs};
  END_WRAP
}

CvStatus Net_SetPreferableBackend(Net net, int backend)
{
  BEGIN_WRAP
  net.ptr->setPreferableBackend(backend);
  END_WRAP
}

CvStatus Net_SetPreferableTarget(Net net, int target)
{
  BEGIN_WRAP
  net.ptr->setPreferableTarget(target);
  END_WRAP
}

CvStatus Net_GetPerfProfile(Net net, int64_t *rval)
{
  BEGIN_WRAP
  std::vector<double> layersTimes;
  *rval = net.ptr->getPerfProfile(layersTimes);
  END_WRAP
}

CvStatus Net_GetUnconnectedOutLayers(Net net, VecInt *rval)
{
  BEGIN_WRAP
  auto cids = new std::vector<int>(net.ptr->getUnconnectedOutLayers());
  *rval = {cids};
  END_WRAP
}

CvStatus Net_GetLayerNames(Net net, VecVecChar *rval)
{
  BEGIN_WRAP
  auto vec = new std::vector<std::vector<char>>();

  std::vector<cv::String> cstrs = net.ptr->getLayerNames();
  for (size_t i = 0; i < cstrs.size(); i++) {
    std::vector<char> cstr(cstrs[i].begin(), cstrs[i].end());
    vec->push_back(cstr);
  }
  *rval = {vec};
  END_WRAP
}

CvStatus Net_GetInputDetails(Net net, VecFloat *scales, VecInt *zeropoints)
{
  BEGIN_WRAP
  auto sc = new std::vector<float>();
  auto zp = new std::vector<int>();
  net.ptr->getInputDetails(*sc, *zp);
  *scales = {sc};
  *zeropoints = {zp};
  END_WRAP
}

CvStatus Net_GetBlobChannel(Mat blob, int imgidx, int chnidx, Mat *rval)
{
  BEGIN_WRAP
  size_t w = blob.ptr->size[3];
  size_t h = blob.ptr->size[2];
  *rval = {new cv::Mat(h, w, CV_32F, blob.ptr->ptr<float>(imgidx, chnidx))};
  END_WRAP
}

CvStatus Net_GetBlobSize(Mat blob, Scalar *rval)
{
  BEGIN_WRAP
  *rval = {
      (double)(blob.ptr->size[0]),
      (double)(blob.ptr->size[1]),
      (double)(blob.ptr->size[2]),
      (double)(blob.ptr->size[3]),
  };
  END_WRAP
}

CvStatus Net_GetLayer(Net net, int layerid, Layer *rval)
{
  BEGIN_WRAP
  *rval = {new cv::Ptr<cv::dnn::Layer>(net.ptr->getLayer(layerid))};
  END_WRAP
}

CvStatus Layer_InputNameToIndex(Layer layer, const char *name, int *rval)
{
  BEGIN_WRAP
  *rval = (*layer.ptr)->inputNameToIndex(name);
  END_WRAP
}

CvStatus Layer_OutputNameToIndex(Layer layer, const char *name, int *rval)
{
  BEGIN_WRAP
  *rval = (*layer.ptr)->outputNameToIndex(name);
  END_WRAP
}

CvStatus Layer_GetName(Layer layer, VecChar *rval)
{
  BEGIN_WRAP
  auto ss = (*layer.ptr)->name;
  *rval = {new std::vector<char>(ss.c_str(), ss.c_str() + ss.size())};
  END_WRAP
}

CvStatus Layer_GetType(Layer layer, VecChar *rval)
{
  BEGIN_WRAP
  auto ss = (*layer.ptr)->type;
  *rval = {new std::vector<char>(ss.c_str(), ss.c_str() + ss.size())};
  END_WRAP
}

void Layer_Close(Layer *layer){CVD_FREE(layer)}

CvStatus
    NMSBoxes(VecRect bboxes, VecFloat scores, float score_threshold, float nms_threshold, VecInt *indices)
{
  BEGIN_WRAP
  VecInt_CPP v = new std::vector<int>();
  cv::dnn::NMSBoxes(*bboxes.ptr, *scores.ptr, score_threshold, nms_threshold, *v, 1.f, 0);
  *indices = {v};
  END_WRAP
}

CvStatus NMSBoxesWithParams(VecRect bboxes, VecFloat scores, const float score_threshold,
                            const float nms_threshold, VecInt *indices, const float eta, const int top_k)
{
  BEGIN_WRAP
  VecInt_CPP v = new std::vector<int>();
  cv::dnn::NMSBoxes(*bboxes.ptr, *scores.ptr, score_threshold, nms_threshold, *v, eta, top_k);
  *indices = {v};
  END_WRAP
}
