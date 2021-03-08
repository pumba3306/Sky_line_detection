#include "Class.h"

Object_orientation::Object_orientation(const cv::Moments* mu, const int& index)
{
    barycenter_x = mu[index].m10/mu[index].m00;
    barycenter_y = mu[index].m01/mu[index].m00;

    double a, b, c;

    a = mu[index].m20/mu[index].m00 - pow(barycenter_x,2); // mu'20
    b = 2*(mu[index].m11/mu[index].m00 - barycenter_x * barycenter_y); // mu'11
    c = mu[index].m02/mu[index].m00 - pow(barycenter_y,2); // mu'02

    if(a - c != 0)
    {
        double arg = 2 * b/(a - c);
        angle = atan( arg ) / 2;
        /*
        double arg = 2 * mu[index].mu11/(mu[index].mu20 - mu[index].mu02);
        angle = atan(arg)/2;
         */
    }

    //double semi_major_axis;
    //double semi_minor_axis;

    if( pow(b,2) + pow(a - c,2) > 0 &&
        a + c + sqrt(pow(b,2) + pow(a - c,2)) > 0 )
    {
        semi_major_axis = sqrt(8 * (a + c + sqrt(pow(b,2) + pow(a - c,2)) ));
        semi_minor_axis = sqrt(8 * (a + c - sqrt(pow(b,2) + pow(a - c,2)) ));
        if(semi_major_axis != 0 &&
           1 - pow(semi_minor_axis,2) / pow(semi_major_axis,2) > 0 )
        {
            /* отношение главной полуоси к побочной */
            elongation = semi_major_axis / semi_minor_axis;

            /* эксцентриситет */
            //elongation = sqrt(1 - pow(semi_minor_axis,2) / pow(semi_major_axis,2) );

            //elongation = sqrt(pow(semi_major_axis,2) - pow(semi_minor_axis,2))/a;

        }
    }
};