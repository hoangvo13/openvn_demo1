// Reading and writing pixel values
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
  Mat grayFrame;   // the "gray" version of the frame
  Mat previousFrame;  // contain the "previous" frame
  Mat grayPreviousFrame;  // the "gray" version of the previous frame
  Mat frameDiff;   // the difference between the current and previous frame
  Mat grayDiff;  // the gray scale of frameDiff

  char videoFileName[50] = "rmit-nvl-1.mp4";  // file name
  // VideoCapture cap(videoFileName); // open the video file
  VideoCapture cap(0); // open the default camera
  if(!cap.isOpened()) {  // check if we succeeded
     return -1;   // if the video source did not open, exit the program
  }
  cap >> frame;   // get one frame from the camera
  cvtColor( frame,grayFrame, CV_BGR2GRAY,1 );       // let's make it gray scale

  namedWindow("Frame",CV_WINDOW_NORMAL);  // create a window
  namedWindow("Gray Frame",CV_WINDOW_NORMAL);
  namedWindow("Frame Difference", CV_WINDOW_NORMAL);
  namedWindow("Gray Difference", CV_WINDOW_NORMAL);

  for (frameCount = 0;   ; frameCount++) {   // a loop.  Add 1 to frameCount every iteration
	 frame.copyTo( previousFrame ); // before reading from the camera, make the current frame previous
	 grayFrame.copyTo( grayPreviousFrame ); //  copy the current gray frame to previous

	 if (!cap.read(frame)) { // are we at the end of the video file?
   	   cap.open(videoFileName);
       cap >> frame; // get a new frame from the video
     }
     imshow("Frame", frame);
     cvtColor( frame, grayFrame, CV_BGR2GRAY,1 );       // let's make it gray scale
     imshow("Gray Frame", grayFrame);
     absdiff( frame, previousFrame, frameDiff );  // difference between current frame and previous frame
     imshow("Frame Difference", frameDiff);
     absdiff( grayFrame, grayPreviousFrame, grayDiff );  // difference between current gray frame and previous gray frame
     imshow("Gray Difference", grayDiff);

     // Vec3b( frameCount % 255, 255, 256-(frameCount%255));
     frame.at<Vec3b>(200,100) = Vec3b(0,0,255); // color pixel x,y=100,200 as red
     int c;
     for (c = 100; c < 300; c++) {
    	 frame.at<Vec3b>(50,c) = Vec3b(frameCount % 255,255,256-(frameCount%255)); // change the color of a rectangular block of pixels
     }
     // for (int d = 10; d < 200; d++) {frame.at<Vec3b>(d,100) = Vec3b(0,255,0)}
     // for (int e = 10; e < 200; e++) { frame.at<Vec3b>(e,100) = Vec3b(0,255,0);}

     int i,j;
     for (i = 200; i < 400; i++) { // i will iterate across rows
    	 for (j = 100; j < 200; j++) { // for the given value of i, we iterate j
    		 frame.at<Vec3b>(i,j) = Vec3b(0,255,255); // color pixel i,j as orange

    	 }
     }


     //read and modify the color of a rectangular block of pixels
     Vec3b pix; // each pixel in the color image is a vector of 3 bytes
     unsigned char red, green, blue;
     for (i = 200; i < 400; i++) { // i will iterate across rows
         	 for (j = 300; j < 400; j++) { // for the given value of i, we iterate j
         		 pix = frame.at<Vec3b>(i,j); // color pixel i,j as orange
         		 blue = pix[0]; // blue component, ranging 0..255
         		 green = pix[1]; // green component
         		 red = pix[2]; // red component
         		 frame.at<Vec3b>(i,j) = Vec3b( 255-blue, 255-green, 255-red); // color negative
         	 }
     }

     // read and modify the values of a rectangular block of gray pixels
     // This is a nested loop, which is a loop inside a loop.
     unsigned char grayPixel; // a gray pixel whose values are 0..255
     for (i = 200; i < 400; i++) { // i will iterate across rows
             	 for (j = 300; j < 400; j++) { // for the given value of i, we iterate j
             		 grayPixel = grayFrame.at<unsigned char>(i,j); // copy the gray pixel value
             		 grayPixel = grayPixel / 2; // divide the value by 2
             		 grayFrame.at<unsigned char>(i,j) = grayPixel; // write it back
             	 }
     }

     // computing a simple statistic (sum) from a block of gray pixels

     int motion = 0;
     for (i = 50; i < 150; i++) { // i will iterate across rows
             	 for (j = 50; j < 150; j++) { // for the given value of i, we iterate j
             		 motion = motion + grayDiff.at<unsigned char>(i,j);
             	 }
     }
     // printf("Motion = %9d \n", motion);

     unsigned char centerValue;
     centerValue = grayFrame.at<unsigned char>( grayFrame.rows/2, grayFrame.cols/2);
     printf("The value of the pixel at the center of the grayFrame is %d\n", centerValue);
     if (centerValue < 100) {
    	 rectangle(frame,Rect(100,100,400,300), Scalar(0,0,255), 8);
     }

     imshow("Frame", frame);
     imshow("Gray Frame", grayFrame);

     if (waitKey(20) >= 0) break;   // if the user presses a key, then exit
  }

  return 0;
}
