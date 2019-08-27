#include "VideoSource.h"

#include <utility>

using namespace cv;
using namespace std;

VideoSource::VideoSource(std::string wndTitle, const char* path)
{
  m_camera = (path == nullptr)? cv::VideoCapture(0) : cv::VideoCapture(path);
  m_wndTitle = std::move(wndTitle);
}

/**
 * Capture the current frame, pass it through to
 * the transformation
 */
Mat VideoSource::captureWith(ITransformation &t, bool bShow = false)
{
  // Take a frame snapshot and pass it through
  // the given transformation
  if (!this->m_camera.isOpened())
  {
    cerr << "ERROR: The camera is inaccessible." << endl;
    return Mat();
  }

  // Capture the frame and transform it
  Mat frame;
  this->m_camera >> frame;
  Mat frame_  = t.transform(frame);

  // Display if the window title is specified
  if (!this->m_wndTitle.empty() && bShow)
  {
    namedWindow(this->m_wndTitle, CV_WINDOW_AUTOSIZE);
    imshow(this->m_wndTitle, frame_);
  }

  return frame_;
}

/**
 * Sequentially and endlessly capture frames from the source
 * and process
 */
void VideoSource::captureRealtimeWith(
  ITransformation &t, 
  function<void (Mat)> pipe)
{
  // This will run endlessly unless the user hits a key
  while (true){
    Mat out = this->captureWith(t);
    
    // Pass the output matrix through 
    pipe(out);

    waitKey(3);
  }
}



