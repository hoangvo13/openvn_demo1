#include <cv.h>
#include <highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio/videoio.hpp>

using namespace cv;

int main(  int argc, char** argv ) {

	VideoCapture cap(0);
	Mat frame;
	Mat gray;
	Mat thresholdImage;
	Mat blurredGray;
	Mat cannyEdge;
	int frameCount = 0;
	namedWindow("Frame", CV_WINDOW_NORMAL);
	namedWindow("Gray", CV_WINDOW_NORMAL);
	namedWindow("Threshold", CV_WINDOW_NORMAL);
	namedWindow("Canny Edge", CV_WINDOW_NORMAL);

	for (frameCount = 0;  ; frameCount ++)
	{
		cap >> frame;
		imshow("Frame", frame);
		cvtColor( frame, gray, CV_BGR2GRAY);
		imshow("Gray", gray);
		threshold( gray, thresholdImage, 90, 255, 0);
		imshow("Threshold", thresholdImage);

		GaussianBlur( gray, blurredGray, Size(7,7), 1.5, 1.5);
		Canny( blurredGray, cannyEdge, 0, 30, 3);
		imshow("Canny Edge", cannyEdge);

		circle( frame, Point(300,225), 20, Scalar(0,128,255), 5);
		if (thresholdImage.at<unsigned char>(255,250) == 0)
		{
			rectangle(frame, Rect(50,50,400,350), Scalar(0,0,255), 8);
		}

		imshow("Frame", frame);


		if (waitKey(10) > 0) break;
	}

	return 0;
}
