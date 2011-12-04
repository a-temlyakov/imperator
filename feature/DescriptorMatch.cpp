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
   
    keypoints_ = new Keypoints(image, keypoint_type);
    descriptors_.setDescriptors(image, 
                                keypoints_->getKeypoints(), 
                                descriptor_type);
    
    keypoint_type_ = keypoint_type;
    descriptor_type_ = descriptor_type;
    matcher_type_ = matcher_type;
}

DescriptorMatch::~DescriptorMatch()
{
    delete keypoints_;
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
    descriptors_.setDescriptors(reference_image_, 
                               keypoints_->getKeypoints(),
                               descriptor_type);
}

const Mat& DescriptorMatch::getReferenceImage()
{
    return reference_image_;
}

const vector<KeyPoint>& DescriptorMatch::getKeypoints()
{
    return keypoints_->getKeypoints();
}

const Mat& DescriptorMatch::getDescriptors()
{
    return descriptors_.getDescriptors();
}

const vector<DMatch>& DescriptorMatch::getMatches()
{
    return matches_;
}

void DescriptorMatch::setMatches(const Mat& target_image)
{
    Keypoints target_kp(target_image, keypoint_type_);
    Descriptors target_desc(target_image, 
                            target_kp.getKeypoints(), 
                            descriptor_type_);

    matcher_->match(descriptors_.getDescriptors(), 
                   target_desc.getDescriptors(),
                   matches_);
}

void DescriptorMatch::displayMatches(const Mat& target_image)
{
    //to-do: hack incoming
    Keypoints target_kp(target_image, keypoint_type_);
    //end hack

    Mat imageMatches;
    drawMatches(reference_image_,
                    keypoints_->getKeypoints(),
                    target_image, //hackish
                    target_kp.getKeypoints(), //very hackish
                    matches_,
                    imageMatches,
                    cv::Scalar(0,200,0));

    namedWindow("Matches");
    imshow("Matches", imageMatches);
    waitKey(0);
}

void DescriptorMatch::displayKeypoints()
{
    keypoints_->displayKeypoints();
}
