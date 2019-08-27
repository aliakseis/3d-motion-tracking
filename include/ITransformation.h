#pragma once

#include <opencv2/opencv.hpp>
#include <opencv/cvaux.hpp>


/**
 * Abstract matrix or image transformation interface
 * 
 * {Mat} -> [Transformation T] -> {Mat}
 */
class ITransformation
{
public:
  virtual cv::Mat transform(cv::Mat& input) = 0;
};