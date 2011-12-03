#ifndef DESCRIPTORMATCH_H
#define DESCRIPTORMATCH_H

#include <opencv2/features2d/features2d.hpp>
#include "Keypoints.h"
#include "Descriptors.h"

class DescriptorMatch{
    private:
        Mat reference_image;
        Ptr<cv::DescriptorMatcher> matcher;
        vector<cv::DMatch> matches;
        Keypoints kp_;
        Descriptors descriptors;
        const char* matcher_type;
        const char* keypoint_type;
        const char* descriptor_type;

    public:
        DescriptorMatch();
        DescriptorMatch(Mat& image, 
                        const char* k_type, 
                        const char* d_type, 
                        const char* m_type);
        ~DescriptorMatch();

        void setReferenceImage(Mat& image);
        void setMatcher(const char* m_type);
        void setDescriptors(const char* d_type);
        
        Mat getReferenceImage();
        void getKeypoints(vector<KeyPoint> keypoints);
        Mat getDescriptors();
        vector<cv::DMatch> getMatches();

        void setMatches(Mat& target_image);

        void displayMatches(Mat& target_image);
        void displayKeypoints();
        
};
#endif //DESCRIPTORMATCH_H

