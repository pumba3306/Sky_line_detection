#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

void edit_edges(cv::Mat&);
void fitting_horizon_line(cv::Mat&, Object_orientation&);
unsigned max_object(std::vector<Object_orientation>&);
void play_video(const std::string& filename);