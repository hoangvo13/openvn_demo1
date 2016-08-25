// opencv_demo1.cpp  The basic frame-reading program
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

  char videoFileName[50] = "rmit-nvl-1.mp4";  // name of the source video file
  VideoCapture cap(videoFileName); // open the source (a video file)
  // VideoCapture cap(0);   // open the source (the camera)
  if(!cap.isOpened()) {  // check if we succeeded in opening the source
     return -1;   // if the source did not open, exit the program
  }
  cap >> frame;   // get one frame from the camera

  namedWindow("Raw Image",CV_WINDOW_NORMAL);  // create a window

  Mat savedFrame;
  char fileName[100]; // this string is where the image file name is stored
  namedWindow("Saved Frame", CV_WINDOW_NORMAL); // for displaying our saved frames

  for(frameCount = 0;   ; frameCount++) {   // a loop
     if (!cap.read(frame)) { // get a frame and check if successful
   	   cap.open(videoFileName);  // opens the video file again
         cap >> frame; // get a new frame from the video
     }
     imshow("Raw Image", frame);  // display the frame

     if (frameCount % 100 == 0) {   // save frame 0, 100, 200, 300, ...
         	 frame.copyTo(savedFrame);   // copy the current frame
         	 imshow("Saved Frame", savedFrame);   // show it in the window
         	 sprintf( fileName,"frame-%06d.jpg",frameCount);  // make the file name
         	 imwrite( fileName,savedFrame );  // save as a JPEG file
          }


     if (waitKey(20) >= 0) break;   // if the user presses a key, then exit
  }
  return 0;
}

