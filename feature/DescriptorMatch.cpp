#include "DescriptorMatch.h"
#include <iostream>

DescriptorMatch::DescriptorMatch()
{

}

DescriptorMatch::DescriptorMatch(cv::Mat& image, const char* k_type,
                                 const char* d_type, const char* m_type)
{
    reference_image = image.clone();
    matcher = cv::DescriptorMatcher::create(m_type);
    
    keypoints.setImage(image);
    keypoints.setKeypoints(k_type);
    
    descriptors.setDescriptors(image, keypoints.getKeypoints(), d_type);
    
    matcher_type = m_type;
    keypoint_type = k_type;
    descriptor_type = d_type;
}

DescriptorMatch::~DescriptorMatch()
{

}

void DescriptorMatch::setReferenceImage(cv::Mat& image)
{
    reference_image = image.clone();
}

void DescriptorMatch::setMatcher(const char* m_type)
{
    matcher_type = m_type;
    matcher = cv::DescriptorMatcher::create(m_type);
}

void DescriptorMatch::setKeypoints(const char* k_type)
{
    keypoints.setKeypoints(k_type);
}

void DescriptorMatch::setDescriptors(const char* d_type)
{
    descriptors.setDescriptors(reference_image, 
                               keypoints.getKeypoints(),
                               d_type);
}

cv::Mat DescriptorMatch::getReferenceImage()
{
    return reference_image;
}

std::vector<cv::KeyPoint> DescriptorMatch::getKeypoints()
{
    return keypoints.getKeypoints();
}

cv::Mat DescriptorMatch::getDescriptors()
{
    return descriptors.getDescriptors();
}

std::vector<cv::DMatch> DescriptorMatch::getMatches()
{
    return matches;
}

void DescriptorMatch::setMatches(cv::Mat& target_image)
{
    Keypoints target_kp(target_image, keypoint_type);
    Descriptors target_desc(target_image, 
                            target_kp.getKeypoints(), 
                            descriptor_type);

    matcher->match(descriptors.getDescriptors(), 
                   target_desc.getDescriptors(),
                   matches);
}

void DescriptorMatch::displayMatches(cv::Mat& target_image)
{
    //to-do: hack incoming
    Keypoints target_kp(target_image, keypoint_type);
    //end hack

    cv::Mat imageMatches;
    cv::drawMatches(reference_image,
                    keypoints.getKeypoints(),
                    target_image, //hackish
                    target_kp.getKeypoints(), //very hackish
                    matches,
                    imageMatches,
                    cv::Scalar(255,255,255));

    cv::namedWindow("Matches");
    cv::imshow("Matches", imageMatches);
    cv::waitKey(0);
}

void DescriptorMatch::displayKeypoints()
{
    keypoints.displayKeypoints();
}
