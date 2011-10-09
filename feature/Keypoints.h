#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

#ifndef KEYPOINTS_H
#define KEYPOINTS_H

class Keypoints{
    private:
        cv::Mat image;
        cv::Ptr<cv::FeatureDetector> detector;
        std::vector<cv::KeyPoint> keypoints;

    public:
        Keypoints();
        Keypoints(const cv::Mat&);
        Keypoints(const cv::Mat&, const char*);
        ~Keypoints();

        void setImage(const cv::Mat&);
        void setKeypoints(const char*);
        
        cv::Mat getImage();
        std::vector<cv::KeyPoint> getKeypoints();

        int size();
        void displayKeypoints();
};

#endif //KEYPOINTS_H
