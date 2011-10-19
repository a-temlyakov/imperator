#include "Descriptors.h"

Descriptors::Descriptors()
{

}

Descriptors::Descriptors(const cv::Mat& image, 
                        std::vector<cv::KeyPoint> keypoints, 
                        const char* descriptor_name)
{
    extractor = cv::DescriptorExtractor::create(descriptor_name);
    extractor->compute(image, keypoints, descriptors);
}

Descriptors::~Descriptors()
{

}

void Descriptors::setDescriptors(const cv::Mat& image,
                                 std::vector<cv::KeyPoint> keypoints,
                                 const char* descriptor_name)
{
    extractor = cv::DescriptorExtractor::create(descriptor_name);
    extractor->compute(image, keypoints, descriptors);
}

cv::Mat Descriptors::getDescriptors()
{
    return descriptors;
}

int Descriptors::getDescriptorSize()
{
    return extractor->descriptorSize();
}   

int Descriptors::getDescriptorType()
{
    return extractor->descriptorType();
}

