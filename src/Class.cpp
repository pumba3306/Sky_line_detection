#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include "Class.h"

Object_orientation::Object_orientation(const std::vector<cv::Moments> &mu, const int& index)
{
    double m00 = mu[index].m00,
           m01 = mu[index].m01,
           m10 = mu[index].m10,
           m20 = mu[index].m20,
           m02 = mu[index].m02,
           m11 = mu[index].m11;
    _m00 = m00;
    std::cout << "Area: " << m00 << std::endl;
    std::cout << "m11: " << m11 << std::endl;
    std::cout << "m20: " << m20 << std::endl;
    std::cout << "m02: " << m02 << std::endl;
    std::cout << "m10: " << m10 << std::endl;
    std::cout << "m01: " << m01 << std::endl;
    center_of_mass_x = m10/m00;
    center_of_mass_y = m01/m00;

    std::cout << "xc * yc = " << center_of_mass_x * center_of_mass_y << std::endl;
    std::cout << "m11/m00 = " << m11/m00 << std::endl;

    double a, b, c;

    a = m20/m00 - pow(center_of_mass_x,2); // mu'20
    b = 2*(m11/m00 - center_of_mass_x * center_of_mass_y); // mu'11
    c = m02/m00 - pow(center_of_mass_y,2); // mu'02

    std::cout << " a " << a
              << " b " << b
              << " c " << c
              << std::endl;
    std::cout << "b/(a-c) = " << b/(a-c) << std::endl;
    if(a - c != 0)
    {
        double arg = 2*b/(a - c); //
        angle = atan( arg ) / 2;
    }
    else{ std::cout << "Error, null data" << std::endl; }

    if( pow(b,2) + pow(a - c,2) > 0 &&
        a + c + sqrt(pow(b,2) + pow(a - c,2)) > 0)
    {

        semi_major_axis = sqrt(8*(a + c + sqrt(pow(b,2) + pow(a - c,2))));
        semi_minor_axis = sqrt(8*(a + c - sqrt(pow(b,2) + pow(a - c,2) ) ));
        std::cout << "s_ma_a " << semi_major_axis << std::endl;
        std::cout << "s_mi_a " << semi_minor_axis << std::endl;
        if(semi_minor_axis != 0)
        {
            elongation = semi_major_axis/semi_minor_axis;
            std::cout << "semi_major_axis / semi_minor_axis = " << elongation << std::endl;
        }
    }
    else{ std::cout << "Error, negative or null data" << std::endl; }
};
