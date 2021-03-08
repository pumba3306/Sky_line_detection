#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

class Object_orientation
{
public:

    Object_orientation(const std::vector<cv::Moments> &mu, const int& index);

    double _m00; // момент нулевого порядка - площадь объекта

    double center_of_mass_x;
    double center_of_mass_y;

    double semi_major_axis;
    double semi_minor_axis;

    double elongation;

    double angle;

};
