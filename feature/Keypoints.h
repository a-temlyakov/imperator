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

        //setters
        void setDetector(const char* feature_name);
        void detect(Mat& image, 
                    vector<KeyPoint>& keypoints, 
                    const char* feature_name);

        //getters
        void getKeypoints(vector<KeyPoint>& keypoints);
        int size();

        //displayers
        void displayKeypoints();
};
#endif //KEYPOINTS_H

