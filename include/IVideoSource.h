#include <vector>
#include <functional>
#include <opencv2/opencv.hpp>
#include <opencv/cvaux.hpp>
#include "ITransformation.h"

#pragma once


/**
 * Video source capture interface
 */

class IVideoSource
{
public:
  virtual cv::Mat captureWith(ITransformation &t, bool bShow) = 0;
  virtual void captureRealtimeWith(ITransformation &t, std::function<void (cv::Mat)> pipe) = 0;
};