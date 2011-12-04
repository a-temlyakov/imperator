#ifndef KEYPOINTS_H
#define KEYPOINTS_H

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
        Keypoints(const Mat& image, const char* feature_name);
        ~Keypoints();

        //computers
        const vector<KeyPoint>& computeKeypoints(const char* feature_name);

        //getters
        const vector<KeyPoint>& getKeypoints();

        //displayers
        void displayKeypoints();
};
#endif //KEYPOINTS_H

