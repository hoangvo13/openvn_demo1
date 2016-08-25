#include <vector>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio/videoio.hpp>
using namespace cv;

void saySomething()
{
	printf(" <3 <3 <3 <3 <3 <3 <3 <3 <3 chung ta khong thuoc ve nhau TUNG NUI MTP!!!!\n");
}

// Get two values a and b. Compute the sum and return its value.
int sumTwoValues(int a, int b)
{
	int temp;
	temp = a + b;
	return temp;
}
int avg(int a, int b){
	return (a+b)/2;
}

// Blend image1 and image2 and store the output in imageBlend
void blendTwoImages(Mat image1, Mat image2, Mat imageBlend)
{
	int i,j;
	unsigned char r1, g1, b1;
	unsigned char r2, g2, b2;
	for (i=0; i < image1.rows; i++)
	{
		for (j=0; j < image1.cols; j++)
		{
			r1 = image1.at<Vec3b>(i,j)[2];
			g1 = image1.at<Vec3b>(i,j)[0];
			b1 = image1.at<Vec3b>(i,j)[1];
			r2 = image2.at<Vec3b>(i,j)[2];
			g2 = image2.at<Vec3b>(i,j)[0];
			b2 = image2.at<Vec3b>(i,j)[1];
			imageBlend.at<Vec3b>(i,j) = Vec3b(avg(b1,b2), avg(g1,g2), avg(r1,r2));
		}

	}
}

int main (int argc, char ** argv ){
 VideoCapture cap(0);
 Mat frame;
 Mat firstFrame, blendFrame;

 int n = 10;
 unsigned char R[n];

 int frameCount =0;
 int startRow =200;
 int startCol =300;
 namedWindow("Frame",CV_WINDOW_NORMAL);
 namedWindow("Blend Frame", CV_WINDOW_NORMAL);

 saySomething(); // a function call

 cap >> firstFrame;
 flip( firstFrame, firstFrame, 1);
 cap >> blendFrame;

  for (frameCount = 0; ; frameCount++){
   cap >> frame;
   flip( frame,frame, 1); // flip the frame: 1 for horizontal, 0 for vertical

   int i; // index variable
   for (i=0;i<n;i++){
    R[i] = frame.at<Vec3b>(startRow,sumTwoValues(startCol,i*20))[2];
   }
   for (i=0;i<n;i++){
      rectangle(frame,Rect(sumTwoValues(startCol,i*20), startRow,2,2),Scalar(0,0,255),4);
   }

   // print the values of the array
   if (frameCount % 10 ==0)
   {
	   saySomething();
	   for (i = 0;i<n;i++){
		   printf("%3d  ",R[i]);
		   rectangle(frame,Rect(startCol+i*20,startRow-R[i],5,R[i]), Scalar(0,128,255),5);
	   }
   printf("\n");
   imshow("Frame",frame);
   }

   blendTwoImages( frame,firstFrame,blendFrame);
   imshow("Blend Frame", blendFrame);

   if (waitKey(20)>0) break;
  }







}
// Mat imageA;
// imageA = imread ("change1.jpg");
// namedWindow("Image A", CV_WINDOW_NORMAL);
// imshow ("Image A",imageA);
//
// unsigned char r,g,b;
// b = imageA.at<Vec3b>(200,300)[0];
// g = imageA.at<Vec3b>(200,300)[1];
// r = imageA.at<Vec3b>(200,300)[2];
//
// printf("Red = %3d, Green = %3d, Blue = %3d \n", r, g, b);
// unsigned char redArray[10]; // unsigned char is 8 bit, ranging 0..255
// int i;// index variable
// for (i =0; i<10; i++){
//  redArray[i]=imageA.at<Vec3b>(200,300+i)[2];//store series of red values from (200,300) to (200,309)
// }
// // lets print out the array values
// for (i=0;i<10;i++){
//  printf("i = %2d, red value = %3d \n",i,redArray[i]);
// }
// waitKey(0);
//}
