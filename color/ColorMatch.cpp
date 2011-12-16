#include "ColorMatch.h"

ColorMatch::ColorMatch()
{

}

ColorMatch::ColorMatch(int num_bins)
{
    hist_.setNumBins(num_bins);
}

ColorMatch::~ColorMatch()
{

}
    
void ColorMatch::setReferenceImage(const Mat& image)
{
    reference_hist_ = hist_.getHistogram(image);
}

double ColorMatch::compare(const Mat& target_image)
{
    target_hist_ = hist_.getHistogram(target_image);

    //to-do: allow different comparison methods:
    //       CV_COMP_CORRELL    - correlation
    //       CV_COMP_CHISQR     - chi-square
    //       CV_COMP_INTERSECT  - intersection
    //       CV_COMP_BHATTACHARYYA - Bhattacharyya distance
    //Official Documentaton:
    //  http://opencv.willowgarage.com/documentation/cpp/histograms.html#cv-comparehist
    return compareHist(reference_hist_, target_hist_, CV_COMP_CORREL);
}
