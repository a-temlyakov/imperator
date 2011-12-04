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

const vector<KeyPoint>& Keypoints::computeKeypoints(const char* feature_name)
{
    detector_ = FeatureDetector::create(feature_name);
    detector_->detect(image_, keypoints_);

    return keypoints_;
}

const vector<KeyPoint>& Keypoints::getKeypoints()
{
    return keypoints_;
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
