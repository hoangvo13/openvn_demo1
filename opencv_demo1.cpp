// Sample program
#include <cv.h>   // headers
#include <highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio/videoio.hpp>

using namespace cv;

int main(  int argc, char** argv ) {
  int frameCount = 0;  // current number of frames.  Set its value to 0
  Mat frame;  // create a matrix "Mat" object called frame (an image)

  char videoFileName[50] = "rmit-nvl-1.mp4";  // file name
  // VideoCapture cap(videoFileName); // open the video file
  VideoCapture cap(0);
  if(!cap.isOpened()) {  // check if we succeeded
     return -1;   // if the camera did not open, exit the program
  }
  cap >> frame;   // get one frame from the camera

  namedWindow("Raw Image",CV_WINDOW_NORMAL);  // create a window

  for(frameCount = 0;   ; frameCount++) {   // a loop
     if (!cap.read(frame)) { // get a frame and check if successful
   	   cap.open(videoFileName);
         cap >> frame; // get a new frame from the video
     }
     imshow("Raw Image", frame);  // display the frame
     if (waitKey(20) >= 0) break;   // if the user presses a key, then exit
  }
  return 0;
}
