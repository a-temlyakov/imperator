#include "Descriptors.h"

Descriptors::Descriptors()
{

}

Descriptors::Descriptors(const Mat& image, 
                        vector<KeyPoint> keypoints, 
                        const char* descriptor_type)
{
    extractor_ = DescriptorExtractor::create(descriptor_type);
    extractor_->compute(image, keypoints, descriptors_);
}

Descriptors::~Descriptors()
{

}

const Mat& Descriptors::computeDescriptors(const Mat& image,
                                           vector<KeyPoint> keypoints,
                                           const char* descriptor_type)
{
    extractor_ = DescriptorExtractor::create(descriptor_type);
    extractor_->compute(image, keypoints, descriptors_);
}

const Mat& Descriptors::getDescriptors()
{
    return descriptors_;
}

int Descriptors::getDescriptorSize()
{
    return extractor_->descriptorSize();
}   

int Descriptors::getDescriptorType()
{
    return extractor_->descriptorType();
}

