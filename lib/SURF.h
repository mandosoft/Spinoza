#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/features2d.hpp>
#include "opencv4/opencv2/xfeatures2d.hpp"
using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

class SURF{
//int main(int argc, char** argv){}
    public:
        int run() {
            VideoCapture cap("points.mp4");
            // Set cap to 0 to enable default camera

            if (!cap.isOpened()) {
                cout << "Error opening video stream or file" << endl;
                return -1;
            }

            for (;;) {
                Mat frame;
                cap >> frame;

                //-- Step 1: Detect the keypoints using SURF Detector
                int minHessian = 8000;
                Ptr<SURF> detector = SURF::create(minHessian);
                std::vector<KeyPoint> keypoints;
                detector->detect(frame, keypoints);

                //-- Draw keypoints
                Mat img_keypoints;
                drawKeypoints(frame, keypoints, img_keypoints);

                if (frame.empty()) break;
                imshow("myco_viz", img_keypoints);
                if (waitKey(10) == 27) break; // esc  was set at 27
            }

            cap.release();
            destroyAllWindows();
            return 0;
        }
};