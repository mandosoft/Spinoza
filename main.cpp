#include <opencv4/opencv2/opencv.hpp>
#include "opencv4/opencv2/imgcodecs.hpp"
#include "opencv4/opencv2/highgui.hpp"
#include "opencv4/opencv2/imgproc.hpp"
using namespace std;
using namespace cv;

int main(int argc, char** argv){
    VideoCapture cap("points.mp4");
    // Set cap to 0 to enable default camera

    if (!cap.isOpened()) {
        cout << "Error opening video stream or file" << endl;
        return -1;
    }

    for (;;) {
        Mat frame;
        Mat gray;
        cap >> frame;
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        medianBlur(gray, gray, 5);

        vector<Vec3f> circles;
        HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                     gray.rows/16,  // change this value to detect circles with different distances to each other
                     100, 30, 1, 30 // change the last two parameters
                // (min_radius & max_radius) to detect larger circles
        );

        for(auto & i : circles)
        {
            Vec3i c = i;
            Point center = Point(c[0], c[1]);
            // circle center
            circle( frame, center, 1, Scalar(0,100,100), 3, LINE_AA);
            // circle outline
            int radius = c[2];
            circle( frame, center, radius, Scalar(255,0,255), 3, LINE_AA);
        }

        if (frame.empty()) break;
        imshow("myco_viz", frame);
        waitKey(70);
        //if (waitKey(10) == 10) break; // esc  was set at 27
    }

}
