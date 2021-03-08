#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include "func.h"


int main(){
    //cv::VideoCapture cap("/home/maxim/CLionProjects/Sky_line_detection_video/videos/videoplayback.mp4");
    cv::VideoCapture cap("/home/maxim/CLionProjects/Sky_line_detection_video/videos/30 Days Timelapse at Sea.mp4");
    if(!cap.isOpened())
    {
        std::cout << "Error opening video stream or file" << std::endl;
    }

    while(1)
    {
        cv::Mat frame;
        cap >> frame;

        if (frame.empty())
            break;

        find_horizon_line(frame);

        imshow( "Frame", frame );

        char c = (char) cv::waitKey(24);

        if(c==27)
            break;
    }

    cap.release();

    cv::destroyAllWindows();
    return 0;
}