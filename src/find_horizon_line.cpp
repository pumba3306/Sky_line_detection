#include "Class.h"
#include "func.h"

#define PI 3.14159265

void find_horizon_line(cv::Mat& image_output)
{

    cv::Mat image = image_output.clone();
    cv::cvtColor( image ,  image , cv::COLOR_RGB2GRAY);

    /* для cv::threshold */
    cv::Mat _img = image.clone();

    // Медианный фильтр
    cv::medianBlur(image, image, 3 );

    // Автоопределение пороговых значений
    double ots_thresh_val = cv::threshold(
        _img, _img, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU
    );

    cv::Canny(image, image, ots_thresh_val/2, ots_thresh_val, 3);

    cv::Mat element = getStructuringElement( cv::MORPH_RECT, cv::Size( 3, 3 ), cv::Point( 0, 0 ) );

    //cv::morphologyEx(image, image, cv::MORPH_CLOSE, element);

    cv::dilate(image, image, element);

    std::vector<std::vector<cv::Point>> contours;

    findContours( image, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE );

    //edit_edges(image);

    const size_t number_of_objects = contours.size();

    if(number_of_objects)
    {
        /* моменты объектов */
        cv::Moments mu[number_of_objects];
        /* положения объектов */
        Object_orientation obj_vec[number_of_objects];
        /* нахождение моментов и положений объектов */
        for(size_t i = 0; i != number_of_objects; i++)
        {
            mu[i] = moments(contours[i], true);
            obj_vec[i] = Object_orientation(mu, i);
        }
        /* индекс требуемого объекта в obj_vec */
        unsigned line_index = max_object(obj_vec, number_of_objects);
        /* построение линии (проверка того, что координаты центра масс принадлежат изображению)*/
        if(obj_vec[line_index].barycenter_x < image.cols &&
           obj_vec[line_index].barycenter_y < image.rows)
        {
            fitting_horizon_line(image_output, obj_vec[line_index]);
        }
    }
}