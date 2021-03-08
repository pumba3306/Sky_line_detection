#include "Class.h"

void fitting_horizon_line(cv::Mat& image, const Object_orientation& object)
{
    unsigned y;
    double slope = tan( object.angle/2 );

    /* y(0) */
    double b = object.barycenter_y - slope * object.barycenter_x;

    for(unsigned x = 0; x != image.cols; x++)
    {

        y = slope * x + b;

        /* отображение линии (с проверкой доступа за границы изображения)*/
        if(y >= 5 && y <= image.rows - 5)
        {

            image.at<cv::Vec3b>(y - 1, x)[0] = 0;
            image.at<cv::Vec3b>(y - 1, x)[1] = 255;
            image.at<cv::Vec3b>(y - 1, x)[2] = 255;


            image.at<cv::Vec3b>(y, x)[0] = 0;
            image.at<cv::Vec3b>(y, x)[1] = 255;
            image.at<cv::Vec3b>(y, x)[2] = 255;


            image.at<cv::Vec3b>(y + 1, x)[0] = 0;
            image.at<cv::Vec3b>(y + 1, x)[1] = 255;
            image.at<cv::Vec3b>(y + 1, x)[2] = 255;

            /* построение точки на цетре масс */
            unsigned k = 3;
            for(unsigned y = object.barycenter_y - k;
                    y <= object.barycenter_y + k; y++)
            {
                for(unsigned x = object.barycenter_x - k;
                        x <= object.barycenter_x + k; x++)
                {
                    image.at<cv::Vec3b>(y, x)[0] = 255;
                    image.at<cv::Vec3b>(y, x)[1] = 0;
                    image.at<cv::Vec3b>(y, x)[2] = 0;
                }
            }



        }
    }
}

unsigned max_object(const Object_orientation* obj_vec, const size_t& number_of_objects)
{
    size_t max_length = obj_vec[0].elongation;
    unsigned cnt = 0;
    for(size_t i = 0; i != number_of_objects; i++)
    {
        if(obj_vec[i].elongation > max_length)
        {
            max_length = obj_vec[i].elongation;
            cnt = i;
        }
    }
    return cnt;
}


/* заливка границ изображения */
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
