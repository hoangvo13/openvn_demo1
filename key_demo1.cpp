#include <cv.h>
#include <highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio/videoio.hpp>

using namespace cv;

int main(  int argc, char** argv ) {

	int frameCount = 0;
	Mat frame;

	namedWindow("Frame", CV_WINDOW_NORMAL);
	VideoCapture cap(0);
	int key;
	bool rectOn; // state variable
	rectOn = false; // initial state
	bool cirOn;
	cirOn = true;

	int counter1 = 0;

	for (frameCount = 0; ; frameCount++)
	{
			cap >> frame;
			key = waitKey(10); // if a key is pressed, store it in variable "key"
			if (key == 'r') // if the key pressed is 'r', draw a rectangle
			{
				rectOn = !rectOn;
			}

			if (rectOn)
			{
				counter1 = counter1 + 1; // or counter1++
				if (counter1 == 100)
				{
					rectOn = false;
					counter1 = 0;
				}
			}

			if (rectOn)
			{
				int r = rand() % 256;
				int g = rand() % 256;
				int b = rand() % 256;
				rectangle( frame, Rect(100,100,250,150), Scalar(b,g,r), rand()%10 + 5);
				printf(" red = %d green = %d blue = %d \n", r,g,b);
			}

			if (key == 'c')
			{
				cirOn = !cirOn;
			}
			if (cirOn)
			{
				circle( frame, Point(255,275), 90, Scalar(0,0,255), 5);
			}

			imshow("Frame", frame);

			if (key == 'q') // an
			{
				break; // exit the loop
			}
	}

	printf("Good Bye not see you again!\n");
}
