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
    if(image_.empty())
    {
        std::cout << "Warning: Image is EMPTY\n";
        std::cout << "No keypoints found!" << std::endl;
        
        //return empty keypoints
        keypoints_.clear();
        return keypoints_;
    }

    detector_ = FeatureDetector::create(feature_name);
    detector_->detect(image_, keypoints_);

    return keypoints_;
}

void Keypoints::setImage(const Mat& image)
{
    image_ = image;
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
