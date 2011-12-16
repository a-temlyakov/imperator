#include "DescriptorMatch.h"
#include <iostream>

DescriptorMatch::DescriptorMatch()
{

}

DescriptorMatch::DescriptorMatch(const Mat& image, 
                                 const char* keypoint_type,
                                 const char* descriptor_type, 
                                 const char* matcher_type)
{
    reference_image_ = image;
    matcher_ = DescriptorMatcher::create(matcher_type);
   
    Keypoints_ = new Keypoints(image, keypoint_type);
    Descriptors_.computeDescriptors(image, 
                                Keypoints_->getKeypoints(), 
                                descriptor_type);
    
    keypoint_type_ = keypoint_type;
    descriptor_type_ = descriptor_type;
    matcher_type_ = matcher_type;
}

DescriptorMatch::~DescriptorMatch()
{
    delete Keypoints_;
}

void DescriptorMatch::computeMatches(const Mat& target_image)
{
    Keypoints target_kp(target_image, keypoint_type_);
    
    //store the references for quick look up
    //if displayMatches is called
    target_image__ = target_image;
    target_keypoints__ = target_kp.getKeypoints();

    Descriptors target_desc(target_image, 
                            target_keypoints__, 
                            descriptor_type_);

    matcher_->match(Descriptors_.getDescriptors(), 
                   target_desc.getDescriptors(),
                   matches_);
}

void DescriptorMatch::setReferenceImage(const Mat& image)
{
    reference_image_ = image;
}

void DescriptorMatch::setMatcher(const char* matcher_type)
{
    matcher_type_ = matcher_type;
    matcher_ = DescriptorMatcher::create(matcher_type);
}

void DescriptorMatch::setDescriptors(const char* descriptor_type)
{
    descriptor_type_ = descriptor_type;
    Descriptors_.computeDescriptors(reference_image_, 
                               Keypoints_->getKeypoints(),
                               descriptor_type);
}

void DescriptorMatch::setKeypoints(const char* keypoint_type)
{
    keypoint_type_ = keypoint_type;
    Keypoints_->computeKeypoints(keypoint_type);
}

const vector<KeyPoint>& DescriptorMatch::getKeypoints() const
{
    return Keypoints_->getKeypoints();
}

const Mat& DescriptorMatch::getDescriptors() const
{
    return Descriptors_.getDescriptors();
}

const vector<DMatch>& DescriptorMatch::getMatches() const
{
    return matches_;
}

void DescriptorMatch::displayMatches() const
{
    Mat imageMatches;
    drawMatches(reference_image_,
                    Keypoints_->getKeypoints(),
                    target_image__,
                    target_keypoints__,
                    matches_,
                    imageMatches,
                    Scalar(0,200,0));

    namedWindow("Matches");
    imshow("Matches", imageMatches);
    waitKey(0);
}

void DescriptorMatch::displayKeypoints() const
{
    Keypoints_->displayKeypoints();
}
