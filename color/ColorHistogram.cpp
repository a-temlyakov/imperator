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

void ColorHistogram::setNumBins(int num_bins)
{
    numBins[0] = numBins[1] = numBins[2] = num_bins;
}

int ColorHistogram::getNumBins() const
{
    return numBins[0];
}

const MatND& ColorHistogram::getHistogram(const Mat& image)
{
    calcHist(&image, 
                    1,          //histogram of 1 image only
                    channels,   //the channel used
                    Mat(),      //no mask is used
                    histogram_, //the resulting histogram
                    3,          //it is a 3D histogram
                    numBins,    //number of bins
                    ranges      //pixel value range
                );

    return histogram_;
}

SparseMat ColorHistogram::getSparseHistogram(const Mat& image)
{
    SparseMat hist(3, numBins, CV_32F);
    calcHist(&image, 1, channels, Mat(), hist, 3, numBins, ranges);
    return hist;
}

void ColorHistogram::equalize(const Mat& image, Mat& result)
{
    //to-do: image must be grayscale - check and exit gracefully
    //       if not grayscale
    equalizeHist(image, result);
}
