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
        ColorMatch(int);
        ~ColorMatch();

        void setReferenceImage(const cv::Mat&);
        double compare(const cv::Mat&);
};
