#pragma once

#include <vector>
#include <functional>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cvaux.hpp>
#include "ITransformation.h"
#include "IVideoSource.h"

class VideoSource : public IVideoSource
{
public:
  VideoSource(std::string wndTitle="", const char* path = nullptr);
  virtual cv::Mat captureWith(ITransformation &t, bool bShow) final;
  virtual void captureRealtimeWith(ITransformation &t, std::function<void (cv::Mat)> pipe) final;

protected:
  // Instance of the collaborating camera
  cv::VideoCapture m_camera;
  // Window title (set to empty string if running UI-less)
  std::string m_wndTitle;
};