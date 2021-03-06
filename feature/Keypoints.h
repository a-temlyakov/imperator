#ifndef KEYPOINTS_H
#define KEYPOINTS_H

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

using namespace cv;
using namespace std;

class Keypoints{
    private:
        Mat image_;
        Ptr<FeatureDetector> detector_;
        vector<KeyPoint> keypoints_;

    public:
        Keypoints();
        Keypoints(const Mat& image, const char* feature_type);
        ~Keypoints();

        //computers
        const vector<KeyPoint>& computeKeypoints(const char* feature_type);

        //setters
        void setImage(const Mat& image);
        
        //getters
        const vector<KeyPoint>& getKeypoints() const;

        //displayers
        void displayKeypoints() const;
};
#endif //KEYPOINTS_H

