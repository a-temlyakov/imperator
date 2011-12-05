#ifndef DESCRIPTORS_H
#define DESCRIPTORS_H

#include <opencv2/features2d/features2d.hpp>

using namespace cv;
using namespace std;

class Descriptors{
    private:
        Ptr<DescriptorExtractor> extractor_;
        Mat descriptors_;

    public:
        Descriptors();
        Descriptors(const cv::Mat& image, 
                    vector<KeyPoint> keypoints, 
                    const char* descriptor_type);
        ~Descriptors();

        const Mat& computeDescriptors(const cv::Mat&, 
                            std::vector<cv::KeyPoint>, 
                            const char*);

        const Mat& getDescriptors();
        int getDescriptorSize();
        int getDescriptorType();
};
#endif //DESCRIPTORS_H

