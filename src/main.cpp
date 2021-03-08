#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <cmath>
#include "Class.h"
#include "func.h"

#define PI 3.14159265

int main(){

    //std::string path = "/home/maxim/QT_projects/Skyline_detection/images/infinity-blue-2211659_1280.jpg";
    //std::string path = "/home/maxim/QT_projects/Skyline_detection/images/index.jpeg";
    //std::string path = "/home/maxim/QT_projects/Skyline_detection/images/infinity-blue-2211659_1280_1.jpg";
    //std::string path = "/home/maxim/QT_projects/Skyline_detection/images/test.png";
    //std::string path = "/home/maxim/QT_projects/Skyline_detection/images/big_za636k0a.jpg";
    std::string path = "/home/maxim/CLionProjects/Sky_line_detection/images/15e1a73b838e2d1f101b6cb24166ed1b.jpg";

    play_video("/home/maxim/CLionProjects/Sky_line_detection/videos/videoplayback.mp4");

    cv::Mat image = cv::imread(path, cv::ImreadModes::IMREAD_GRAYSCALE);
    cv::Mat image_output = cv::imread(path);
    cv::Mat _img = cv::imread(path, cv::ImreadModes::IMREAD_GRAYSCALE);

    std::cout << image.cols << std::endl;
    std::cout << image.rows << std::endl;

    if(!image.data)
    {
        std::cout << "Import error" << std::endl;
        return -1;
    }

    // Медианный фильтр
    cv::medianBlur(image, image, 7);
    // Автоопределение пороговых значений по алгоритму OTSU для фильтра Canny
    double otsu_thresh_val = cv::threshold(
        _img, _img, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU
    );

    cv::Canny(image, image, otsu_thresh_val/2, otsu_thresh_val, 3);

    cv::Mat element = getStructuringElement( cv::MORPH_RECT, cv::Size( 3, 3 ), cv::Point( 0, 0 ) );
    // Замыкание
    cv::morphologyEx(image, image, cv::MORPH_CLOSE, element);

    cv::dilate(image, image, element);

    //cv::imwrite("/home/maxim/QT_projects/Skyline_detection/images/_test.jpg", image);
    //std::cout << "type: " << image.type() << std::endl;
    //int i = cv::connectedComponents(image, _image, 8, 2);
    //std::cout << i<< std::endl;

    std::vector<std::vector<cv::Point>> contours;

    findContours( image, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE );
    edit_edges(image);

    std::cout << contours.size() << std::endl;
    std::vector<cv::Moments> mu(contours.size());
    std::vector<Object_orientation> obj_vec;

    for(size_t i = 0; i != contours.size(); i++)
    {
        mu[i] = moments(contours[i], true);
        obj_vec.emplace_back(Object_orientation(mu, i));

        std::cout << "Координаты: row = " << round(obj_vec[i].center_of_mass_y)
                  << "     col = " << round(obj_vec[i].center_of_mass_x)
                  << "     Угол наклона (deg) = " << (obj_vec[i].angle)*180/PI
                  << "     Длина объекта = " << 2*obj_vec[i].semi_major_axis
                  << "     Area = " << obj_vec[i]._m00 << std::endl;

        std::cout << "________________" << std::endl;

    }

    unsigned line_index = max_object(obj_vec);

    std::cout << " Координаты линии горизонта: row = "
              << round(obj_vec[line_index].center_of_mass_y)
              << " col = "
              << round(obj_vec[line_index].center_of_mass_x)
              << " Угол наклона линии горизонта (deg) = "
              << obj_vec[line_index].angle*180/PI
              << " Тангенс угла наклона = "
              << tan(obj_vec[line_index].angle)
              << std::endl;

    fitting_horizon_line(image_output, obj_vec[line_index]);


    cv::namedWindow("image",cv::WINDOW_AUTOSIZE);
    //cv::imshow("image", image);
    cv::imshow("image", image_output);
    cv::waitKey(0);

    return 0;
}
