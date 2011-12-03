#ifndef COLORHISTOGRAM_H
#define COLORHISTOGRAM_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


class ColorHistogram{
    private:
        int numBins[3];
        float hranges[2];
        const float* ranges[3];
        int channels[3];

    public:
        ColorHistogram();
        ColorHistogram(int num_bins);
        ~ColorHistogram();

        int getNumBins();
        cv::MatND getHistogram(const cv::Mat& image);
        cv::SparseMat getSparseHistogram(const cv::Mat& image);
        
        void setNumBins(int num_bins);

        cv::Mat equalize(const cv::Mat& image);

};
#endif //COLORHISTOGRAM_H

