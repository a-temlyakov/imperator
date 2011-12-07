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
//
const Mat& Descriptors::computeDescriptors(const Mat& image,
                                           vector<KeyPoint> keypoints,
                                           const char* descriptor_type)
{
    extractor_ = DescriptorExtractor::create(descriptor_type);
    extractor_->compute(image, keypoints, descriptors_);

    return descriptors_;
}

const Mat& Descriptors::getDescriptors() const
{
    return descriptors_;
}

int Descriptors::getDescriptorSize() const
{
    return extractor_->descriptorSize();
}   

int Descriptors::getDescriptorType() const
{
    return extractor_->descriptorType();
}

