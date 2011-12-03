#include "Keypoints.h"

Keypoints::Keypoints()
{
    
}

Keypoints::Keypoints(const Mat& image, const char* feature_name)
{
    image_ = image;
    detector_ = FeatureDetector::create(feature_name);
    detector_->detect(image, keypoints_);
}

Keypoints::~Keypoints()
{

}

void Keypoints::setDetector(const char* feature_name)
{
    detector_ = FeatureDetector::create(feature_name);
}

void Keypoints::detect(Mat& image, 
                       vector<KeyPoint>& keypoints, 
                       const char* feature_name)
{
    image_ = image;
    detector_ = FeatureDetector::create(feature_name);
    detector_->detect(image, keypoints_);
    keypoints = keypoints_;
}

void Keypoints::getKeypoints(vector<KeyPoint>& keypoints)
{
    keypoints = keypoints_;
}

int Keypoints::size()
{
    return keypoints_.size();
}

void Keypoints::displayKeypoints()
{
    Mat keypoints_image;
    drawKeypoints(image_,
                      keypoints_,
                      keypoints_image,
                      Scalar(0,0,255),
                      DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    namedWindow("Image Keypoints");
    imshow("Image Keypoints", keypoints_image);
    waitKey(0);
}
