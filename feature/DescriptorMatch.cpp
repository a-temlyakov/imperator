#include "DescriptorMatch.h"
#include <iostream>

DescriptorMatch::DescriptorMatch()
{

}

DescriptorMatch::DescriptorMatch(Mat& image, const char* k_type,
                                 const char* d_type, const char* m_type)
{
    reference_image = image.clone();
    matcher = DescriptorMatcher::create(m_type);
    
    vector<KeyPoint> keypoints;
    kp_.detect(image, keypoints, k_type);

    descriptors.setDescriptors(image, keypoints, d_type);
    
    matcher_type = m_type;
    keypoint_type = k_type;
    descriptor_type = d_type;
}

DescriptorMatch::~DescriptorMatch()
{

}

void DescriptorMatch::setReferenceImage(Mat& image)
{
    reference_image = image.clone();
}

void DescriptorMatch::setMatcher(const char* m_type)
{
    matcher_type = m_type;
    matcher = DescriptorMatcher::create(m_type);
}

void DescriptorMatch::setDescriptors(const char* d_type)
{
    vector<KeyPoint> keypoints;
    kp_.getKeypoints(keypoints);
    descriptors.setDescriptors(reference_image, 
                               keypoints,
                               d_type);
}

Mat DescriptorMatch::getReferenceImage()
{
    return reference_image;
}

void DescriptorMatch::getKeypoints(vector<KeyPoint> keypoints)
{
    kp_.getKeypoints(keypoints);
}

Mat DescriptorMatch::getDescriptors()
{
    return descriptors.getDescriptors();
}

vector<DMatch> DescriptorMatch::getMatches()
{
    return matches;
}

void DescriptorMatch::setMatches(Mat& target_image)
{
    vector<KeyPoint> target_keypoints;
    Keypoints target_kp;
    target_kp.detect(target_image, target_keypoints, keypoint_type);
    Descriptors target_desc(target_image, 
                            target_keypoints, 
                            descriptor_type);

    matcher->match(descriptors.getDescriptors(), 
                   target_desc.getDescriptors(),
                   matches);
}

void DescriptorMatch::displayMatches(Mat& target_image)
{
    //to-do: hack incoming
    vector<KeyPoint> template_keypoints, target_keypoints;
    Keypoints target_kp;
    target_kp.detect(target_image, target_keypoints, keypoint_type);
    kp_.getKeypoints(template_keypoints);
    //end hack

    Mat imageMatches;
    drawMatches(reference_image,
                    template_keypoints,
                    target_image, //hackish
                    target_keypoints, //very hackish
                    matches,
                    imageMatches,
                    cv::Scalar(255,255,255));

    namedWindow("Matches");
    imshow("Matches", imageMatches);
    waitKey(0);
}

void DescriptorMatch::displayKeypoints()
{
    kp_.displayKeypoints();
}
