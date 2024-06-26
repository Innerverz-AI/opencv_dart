#include "../dnn/dnn.h"
#include "../core/core.h"
#include <gtest/gtest.h>
#include <fstream>
// #include <opencv/opencv.hpp>
#include <stdint.h>
#include <stdio.h>
#include <vector>

std::vector<uchar> readFile(const char* filename)
{
    // open the file:
    std::ifstream file(filename, std::ios::binary);

    // Stop eating new lines in binary mode!!!
    file.unsetf(std::ios::skipws);

    // get its size:
    std::streampos fileSize;

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // reserve capacity
    std::vector<uchar> vec;
    vec.reserve(fileSize);

    // read the data:
    vec.insert(vec.begin(),
               std::istream_iterator<uchar>(file),
               std::istream_iterator<uchar>());

    return vec;
}

TEST(dnn, Create)
{
  Net net;
  auto data = readFile("test/models/bvlc_googlenet.caffemodel");
  auto conf = readFile("test/models/bvlc_googlenet.prototxt");
  VecUChar bufM = {&data};
  VecUChar bufC = {&conf};
  CvStatus status = Net_ReadNetBytes("caffe", bufM, bufC, &net);
  EXPECT_EQ(status.code, 0);
  EXPECT_EQ(net.ptr->empty(), false);
  VecChar dump = {new std::vector<char>()};
  Net_Dump(net, dump);
  std::cout << dump.ptr->size() << std::endl;
}