#ifndef DESCRIPTORS_H
#define DESCRIPTORS_H

#include <opencv2/features2d/features2d.hpp>

class Descriptors{
    private:
        cv::Ptr<cv::DescriptorExtractor> extractor;
        cv::Mat descriptors;

    public:
        Descriptors();
        Descriptors(const cv::Mat&, std::vector<cv::KeyPoint>, const char*);
        ~Descriptors();

        void setDescriptors(const cv::Mat&, 
                            std::vector<cv::KeyPoint>, 
                            const char*);

        cv::Mat getDescriptors();
        int getDescriptorSize();
        int getDescriptorType();
};
#endif //DESCRIPTORS_H

