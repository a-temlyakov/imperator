#include "ColorMatch.h"

ColorMatch::ColorMatch()
{

}

ColorMatch::ColorMatch(int num_bins)
{
    hist.setNumBins(num_bins);
}

ColorMatch::~ColorMatch()
{

}
    
void ColorMatch::setReferenceImage(const cv::Mat& image)
{
    refH = hist.getHistogram(image);
}

double ColorMatch::compare(const cv::Mat& target_image)
{
    inputH = hist.getHistogram(target_image);
    return cv::compareHist(refH, inputH, CV_COMP_CORREL);
}
