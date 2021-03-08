#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include "Class.h"

void find_horizon_line(cv::Mat&);

unsigned max_object(const Object_orientation*, const size_t&);

void fitting_horizon_line(cv::Mat&, const Object_orientation&);


void play_video(const std::string&);
void edit_edges(cv::Mat&);