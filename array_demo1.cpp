#include <cv.h>
#include <highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio/videoio.hpp>

using namespace cv;

int main(  int argc, char** argv ) {

	Mat imageA;

	imageA = imread("lionking.jpg");
	namedWindow("Image A", CV_WINDOW_NORMAL);
	imshow("Image A", imageA);

	unsigned char r, g, b;

	b = imageA.at<Vec3b>(200, 300)[0];
	g = imageA.at<Vec3b>(200, 300)[1];
	r = imageA.at<Vec3b>(200, 300)[2];

	printf("Red = %d, Green = %d, Blue = %d \n", r,g,b);

	// an array with 10 elements
	unsigned char redArray[10]; // unsigned char is 8 bits (1 byte), ranging 0..255
	int i; // index variable
	for (i = 0; i<10; i++)
	{
		redArray[i] = imageA.at<Vec3b>(200, 300 + i)[2]; // store a series of red values
	}

	// let's print out the array values
	for (i = 0; i < 10; i++)
	{
		printf("i = %d, red value = %d \n", i, redArray[i]);
	}

	waitKey(0);

}
