#include "Keypoints.h"

Keypoints::Keypoints()
{
    
}

Keypoints::Keypoints(const cv::Mat& img)
{
    image = img.clone();
}

Keypoints::Keypoints(const cv::Mat& img, const char* feature)
{
    image = img.clone();
    detector = cv::FeatureDetector::create(feature);
    detector->detect(image, keypoints);
}

Keypoints::~Keypoints()
{

}

void Keypoints::setImage(const cv::Mat& img)
{
    image = img.clone();
}

void Keypoints::setKeypoints(const char* feature)
{
    detector = cv::FeatureDetector::create(feature);
    detector->detect(image, keypoints);
}

cv::Mat Keypoints::getImage()
{
    return image;
}

std::vector<cv::KeyPoint> Keypoints::getKeypoints()
{
    return keypoints;
}

int Keypoints::size()
{
    return keypoints.size();
}

void Keypoints::displayKeypoints()
{
    cv::Mat keypoints_image;
    cv::drawKeypoints(image,
                      keypoints,
                      keypoints_image,
                      cv::Scalar(0,0,255),
                      cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    cv::namedWindow("Image Keypoints");
    cv::imshow("Image Keypoints", keypoints_image);
    cv::waitKey(0);
}
