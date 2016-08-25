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
  Mat previousFrame;  // contain the "previous" frame
  Mat frameDiff;   // the difference between the current and previous frame
  Mat grayDiff;  // the gray scale of frameDiff

  char videoFileName[50] = "rmit-nvl-1.mp4";  // file name
  // VideoCapture cap(videoFileName); // open the video file
  VideoCapture cap(0); // open the default camera
  if(!cap.isOpened()) {  // check if we succeeded
     return -1;   // if the camera did not open, exit the program
  }
  cap >> frame;   // get one frame from the camera

  int motion;
  int previousMotion;
  int x,y;
  int xRoi = 300; // top-left x
  int yRoi = 125; // top-left y
  int widthRoi = 100;  // width of the roi
  int heightRoi = 100;  // height
  float threshold = 1.75;
  int count = 0;   // holds the number of objects we counted so far

  float sum = 0.0;   // running sum
  float averageMotion;

  namedWindow("Camera",CV_WINDOW_NORMAL);  // create a window
  namedWindow("Frame Difference", CV_WINDOW_NORMAL);
  namedWindow("Gray Difference", CV_WINDOW_NORMAL);

  Mat savedFrame;
    char fileName[100]; // this string is where the image file name is stored
    namedWindow("Saved Frame", CV_WINDOW_NORMAL); // for displaying our saved frames

    FILE *file1;
    file1 = fopen("detected_objects.html","wt");  // open the file for writing text
    fprintf( file1, "<html><body><br>\n");  // write the HTML header into the text file


  for(frameCount = 0;   ; frameCount++) {   // a loop.  Add 1 to frameCount every iteration
	 frame.copyTo( previousFrame ); // before reading from the camera, make the current frame previous
     if (cap.read(frame) == NULL) { // are we at the end of the video file?
   	   cap.open(videoFileName);
       cap >> frame; // get a new frame from the video
     }
//	 cap >> frame;  // get one frame from the camera
	 rectangle( frame,Rect(xRoi,yRoi,widthRoi,heightRoi), Scalar(0,0,255), 8);
     imshow("Camera", frame);  // display the frame
     // compute the absolute difference between frame and previousFrame and store it in frameDiff
     absdiff( frame,previousFrame,frameDiff );
     imshow("Frame Difference", frameDiff);
     cvtColor( frameDiff,grayDiff, CV_BGR2GRAY,1 );       // let's make it gray scale
     imshow("Gray Difference", grayDiff);
     previousMotion = motion;  // save the motion as previous, before re-computing
     motion = 0;  // the sum is 0
     for (x = xRoi; x < xRoi+widthRoi; x++) {  // every x inside the ROI
    	 for (y = yRoi; y < yRoi+heightRoi; y++) {  // every y insdie the ROI
    		 motion = motion + grayDiff.at<unsigned char>(y,x);   // take the value at that x,y location and add to motion
    	 }
     }

     sum = sum + motion;  // running sum of motion values
     averageMotion = sum / frameCount;   // running average

     // if previousMotion is below the threshold and current is above the threshold
     // the we have a new object
     if (previousMotion <= averageMotion * threshold
    		 && motion > averageMotion * threshold) {
        count = count + 1;  // increase the count
        // visualize the count increase on the image using a different colored rectangle
        rectangle( frame,Rect(xRoi,yRoi,widthRoi,heightRoi), Scalar(0,255,255), 8);
        imshow("Camera", frame);  // display the frame

        frame.copyTo(savedFrame);   // copy the current frame
        imshow("Saved Frame", savedFrame);   // show it in the window
        sprintf( fileName,"frame-%06d.jpg",frameCount);  // make the file name
        imwrite( fileName,savedFrame );  // save as a JPEG file

        fprintf( file1, "This is frame %06d <img src = \"frame-%06d.jpg\"><br>\n",
        frameCount,frameCount);   // save a text line in the HTML file

     }
     printf("frameCount = %d Motion = %8d averageMotion = %2.0f Count = %4d\n",
    	frameCount,motion,averageMotion,count); // %8d means an integer occupying 8 characters
     if (waitKey(20) >= 0) break;   // if the user presses a key, then exit
  }

  fclose(file1);  // close the file
  return 0;
}
