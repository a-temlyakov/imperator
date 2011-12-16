#ifndef COLORHISTOGRAM_H
#define COLORHISTOGRAM_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

class ColorHistogram{
    private:
        int numBins[3];
        float hranges[2];
        const float* ranges[3];
        int channels[3];
        MatND histogram_;

    public:
        ColorHistogram();
        ColorHistogram(int num_bins);
        ~ColorHistogram();

        //setters
        void setNumBins(int num_bins);

        //getters
        int getNumBins() const;
        const MatND& getHistogram(const Mat& image);
        SparseMat getSparseHistogram(const Mat& image);

        void equalize(const Mat& image, Mat& result);

};
#endif //COLORHISTOGRAM_H

