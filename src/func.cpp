#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include "Class.h"

#define PI 3.14159265

void fitting_horizon_line(cv::Mat& image, Object_orientation& object)
{
    std::cout << "Angle " << object.angle*180/PI << std::endl;
    std::cout << "Length " << object.semi_major_axis << std::endl;
    int y;
    double slope = tan(object.angle / 2);
    double b = object.center_of_mass_y - slope*object.center_of_mass_x;

    for(int x = 0; x != image.cols; x++)
    {


        y = slope * x + b;


        image.at<cv::Vec3b>(y - 1, x)[0] = 0;
        image.at<cv::Vec3b>(y - 1, x)[1] = 0;
        image.at<cv::Vec3b>(y - 1, x)[2] = 255;

        image.at<cv::Vec3b>(y, x)[0] = 0;
        image.at<cv::Vec3b>(y, x)[1] = 0;
        image.at<cv::Vec3b>(y, x)[2] = 255;

        image.at<cv::Vec3b>(y + 1, x)[0] = 0;
        image.at<cv::Vec3b>(y + 1, x)[1] = 0;
        image.at<cv::Vec3b>(y + 1, x)[2] = 255;

    }

    int k = 3;

    for(int y = object.center_of_mass_y - k; y <= object.center_of_mass_y + k; y++)
    {
        for(int x = object.center_of_mass_x - k; x <= object.center_of_mass_x + k; x++)
        {

            image.at<cv::Vec3b>(y, x)[0] = 0;
            image.at<cv::Vec3b>(y, x)[1] = 255;
            image.at<cv::Vec3b>(y, x)[2] = 0;


        }
    }
}

void play_video(const std::string& filename)
{
    cv::VideoCapture cap(filename);

    if(!cap.isOpened())
    {
        std::cout << "Error opening video stream or file" << std::endl;
    }

    while(1){
        cv::Mat frame;
        // Capture frame-by-frame
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty())
            break;

        // Display the resulting frame
        imshow( "Frame", frame );

        // Press  ESC on keyboard to exit
        char c=(char)cv::waitKey(25);
        if(c==27)
            break;
    }

    // When everything done, release the video capture object
    cap.release();

    // Closes all the frames
    cv::destroyAllWindows();
}

unsigned max_object(std::vector<Object_orientation>& obj_vec)
{
    size_t max_length = obj_vec[0].elongation;
    unsigned cnt = 0;
    for(size_t i = 0; i != obj_vec.size(); i++)
    {
        if(obj_vec[i].elongation > max_length)
        {
            max_length = obj_vec[i].elongation;
            cnt = i;
        }
    }
    return cnt;
}

/* заливка границ */
void edit_edges(cv::Mat& image)
{
    // верхняя граница
    for(int row = 0; row != 10; row++)
    {
        for(int col = 0; col != image.cols; col++)
        {
            image.at<uchar>(row,col) = 0;
        }
    }
    // нижняя граница
    for(int row = image.rows - 11; row != image.rows; row++)
    {
        for(int col = 0; col != image.cols; col++)
        {
            image.at<uchar>(row,col) = 0;
        }
    }
    // левая граница
    for(int col = 0; col != 10; col++)
    {
        for(int row = 0; row != image.rows; row++)
        {
            image.at<uchar>(row,col) = 0;
        }
    }
    //правая граница
    for(int col = image.cols - 11; col != image.cols; col++)
    {
        for(int row = 0; row != image.rows; row++)
        {
            image.at<uchar>(row,col) = 0;
        }
    }
}
