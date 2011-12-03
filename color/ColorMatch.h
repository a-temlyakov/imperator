#ifndef COLORMATCH_H
#define COLORMATCH_H

#include "ColorHistogram.h"

class ColorMatch{
    private:
        cv::Mat reference;
        cv::Mat input;
        cv::MatND refH;
        cv::MatND inputH;
        ColorHistogram hist;

    public:
        ColorMatch();
        ColorMatch(int num_bins);
        ~ColorMatch();

        void setReferenceImage(const cv::Mat& image);
        double compare(const cv::Mat& target_image);
};
#endif //COLORMATCH_H

