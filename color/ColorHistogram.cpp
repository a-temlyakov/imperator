#include "ColorHistogram.h"
#include <iostream>

ColorHistogram::ColorHistogram()
{
    // Prepare arguments for a color histogram
    numBins[0] = numBins[1] = numBins[2] = 256;
    
    //RGB range
    hranges[0] = 0.0; 
    hranges[1] = 255.0;

    //All channels have the same range
    ranges[0] = hranges;
    ranges[1] = hranges;
    ranges[2] = hranges;

    //The three channels
    channels[0] = 0;
    channels[1] = 1;
    channels[2] = 2;
}

ColorHistogram::ColorHistogram(int num_bins)
{
    numBins[0] = numBins[1] = numBins[2] = num_bins;

    hranges[0] = 0.0;
    hranges[1] = 255.0;

    ranges[0] = hranges;
    ranges[1] = hranges;
    ranges[2] = hranges;

    channels[0] = 0;
    channels[1] = 1;
    channels[2] = 2;
}

ColorHistogram::~ColorHistogram()
{

}

int ColorHistogram::getNumBins()
{
    return numBins[0];
}

cv::MatND ColorHistogram::getHistogram(const cv::Mat& image)
{
    cv::MatND hist;

    cv::calcHist(&image, 
                    1,          //histogram of 1 image only
                    channels,   //the channel used
                    cv::Mat(),  //no mask is used
                    hist,       //the resulting histogram
                    3,          //it is a 3D histogram
                    numBins,   //number of bins
                    ranges     //pixel value range
                );

    return hist;
}

cv::SparseMat ColorHistogram::getSparseHistogram(const cv::Mat& image)
{
    cv::SparseMat hist(3, numBins, CV_32F);
    cv::calcHist(&image, 1, channels, cv::Mat(), hist, 3, numBins, ranges);
    return hist;
}

void ColorHistogram::setNumBins(int num_bins)
{
    numBins[0] = numBins[1] = numBins[2] = num_bins;
}

cv::Mat equalize(const cv::Mat& image)
{
    cv::Mat result;
    cv::equalizeHist(image, result);
    return result;
}
