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
        ColorHistogram(int);
        ~ColorHistogram();

        int getNumBins();
        cv::MatND getHistogram(const cv::Mat&);
        cv::SparseMat getSparseHistogram(const cv::Mat&);
        
        void setNumBins(int);

        cv::Mat equalize(const cv::Mat&);

};
