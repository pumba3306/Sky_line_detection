#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

class Object_orientation
{
public:
    Object_orientation() = default;
    Object_orientation(const cv::Moments*, const int&);
    double semi_major_axis;
    double semi_minor_axis;

    double barycenter_x;
    double barycenter_y;

    double elongation;

    double angle;
};