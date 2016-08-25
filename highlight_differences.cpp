#include <cv.h>
#include <highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio/videoio.hpp>

using namespace cv;

int main(  int argc, char** argv ) {

	Mat image1, image4, highlight;

	image1 = imread("change1.jpg"); // read an image, store in image1
	namedWindow("Display image 1",CV_WINDOW_NORMAL); // create the window
	imshow("Display image 1",image1); // show the image in the window

	image4 = imread("change4.jpg"); // read an image, store in imageA
	namedWindow("Display image 4",CV_WINDOW_NORMAL); // create the window
	imshow("Display image 4",image4); // show the image in the window

	image4.copyTo( highlight ); // copy image4 to highlight
	namedWindow("Display highlight",CV_WINDOW_NORMAL); // create the window
	imshow("Display highlight",highlight); // show the image in the window

	int i,j;
	Vec3b pixA, pixB; // will contain the current RGB pixel
	unsigned char red1, green1, blue1; // red(0..255), green(0..255) and blue contain the RG
	unsigned char red2, green2, blue2;

	VideoCapture cap(0);
	cap >> image1;

for ( ; ; ) {
	cap >> image4;

	for (i=0;i<image1.rows;i++) { // visit every row
		for (j=0;j<image1.cols;j++) { // for row i, visit every column
			// highlight.at<Vec3b>(i,j) = Vec3b(0,0,255); // set pixel i,j to red
			// imshow("Display highlight", highlight); // show
			// if (waitKey(1) >= 0) break;
			pixA = image1.at<Vec3b>(i,j); // color pixel i,j of image1
			blue1 = pixA[0];
			green1 = pixA[1];
			red1 = pixA[2];
			pixB = image4.at<Vec3b>(i,j); // color pixel i,j of image4
			blue2 = pixB[0];
			green2 = pixB[1];
			red2 = pixB[2];

			highlight.at<Vec3b>(i,j) = Vec3b((red1+red2)/2,(green1+green2)/2,(blue1+blue2)/2);

	//		if (abs(blue1 - blue2) > 20 || abs(red1 - red2) > 20 || abs(green1 - green2) > 20) {
	//			highlight.at<Vec3b>(i,j) = Vec3b(0,255,255); // highlight the significant difference
	//		}

			}
		}

	imshow("Display highlight", highlight);
	if (waitKey(20) >= 0) break;
	}
	waitKey(0); // wait for the user to press a key
	return 0;


}
