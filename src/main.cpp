/**
 * Entry point for 3D motion track app
 * @author TaoPR (StarColon.com)
 * @copyRight 2016-now 
 */

#include "IdentityTransformation.h"
#include "FilterTransformation.h"
#include "VideoSource.h"
#include "ParticleTracker.h"
#include "ITracker.h"

#include <mutex>
#include <functional>

using namespace std;

bool debug              = true;
ITracker* trackerModel  = nullptr;
mutex m;

void mouseEvent(int event, int x, int y, int n, void* p)
{
  if (event == EVENT_LBUTTONDOWN)
  {
    // Point selection
    cout << CYAN << "(" << x << ", " << y << ")" << RESET << endl;
    // TAOTODO: lock trackerModel before proceeding
    trackerModel->addTrackingPoint(Point2i(x, y));
  }
}

function<void (Mat)> createTracker()
{
  trackerModel = new ParticleTracker("sift");
  return trackerModel->track();
}

int main(int argc, char** argv)
{
    try
    {
        // Prepare frame transformers
        IdentityTransformation nothing;
        FilterTransformation grayDownsampling = FilterTransformation(
        FilterType::Nothing, 0, 0, 0.43);
  
        auto tracker = createTracker();
        ITracker::bindMouseEvent(trackerModel->wndName, mouseEvent);

        // Start capturing from video source
        VideoSource cam = (argc >= 2)? VideoSource("video", argv[1]) : VideoSource("cam");
        cam.captureRealtimeWith(grayDownsampling, tracker);
        return 0;
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Fatal: " << ex.what() << '\n';
         return 1;
    }
}
