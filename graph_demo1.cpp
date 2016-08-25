#include <cv.h>
#include <highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio/videoio.hpp>

using namespace cv;

// this function takes an input frame
// and returns (output) the flipped frame
Mat invertFrame(Mat inputFrame) {
	Mat tempFrame; // a local object

	inputFrame.copyTo( tempFrame ); // copy the input frame to our temporary frame
	flip( tempFrame, tempFrame, 1); // do some processing

	return tempFrame; // return this to the caller (main)
}

Mat drawGraph(Mat graphFrame, int value, int column) {
	Mat tempFrame;
	graphFrame.copyTo(tempFrame);
	flip(tempFrame,tempFrame,0); // flip vertically
	rectangle(tempFrame, Rect(column,0,2,graphFrame.cols),
			Scalar(0,0,0), 2); // erase the column before drawing
	rectangle(tempFrame, Rect(column,0,2,value),
			Scalar( rand() % 255, rand() % 255,255), 2);
	flip(tempFrame,tempFrame,0); // flip back
	return tempFrame;
}


int main(  int argc, char** argv ) {

	VideoCapture cap(0);
	Mat frame;
	Mat black, graph;
	int frameCount;
	namedWindow("Frame", CV_WINDOW_NORMAL);
	namedWindow("Inverted Frame", CV_WINDOW_NORMAL);
	namedWindow("Graph Frame", CV_WINDOW_NORMAL);
	cap >> graph;

	for (frameCount = 0;  ; frameCount++) {
		cap >> frame;

		circle(frame, Point(frame.rows/2,frame.cols/2), 5, Scalar(0,128,255), 3);
		imshow("Frame", frame);
		imshow("Inverted Frame", invertFrame(frame)); // we call the function invertFrame()

		// get the blue value (0..255) of the frame's center pixel
		// and draw it on the graph

		graph = drawGraph(graph, frame.at<Vec3b>(frame.rows/2,frame.cols/2)[0],
				frameCount % frame.cols);
		imshow("Graph Frame", graph);
		if (waitKey(10) == 'q') { break; }
	}
}
