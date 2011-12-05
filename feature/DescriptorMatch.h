#ifndef DESCRIPTORMATCH_H
#define DESCRIPTORMATCH_H

#include <opencv2/features2d/features2d.hpp>
#include "Keypoints.h"
#include "Descriptors.h"

class DescriptorMatch{
    private:
        Mat reference_image_;
        Ptr<DescriptorMatcher> matcher_;
        vector<DMatch> matches_;
        Keypoints *Keypoints_;
        Descriptors Descriptors_;
        const char* keypoint_type_;
        const char* descriptor_type_;
        const char* matcher_type_;

        //super-private:
        //these are only used to cache information about the target image
        //currently this information is used in displayMatches()
        Mat target_image__;
        vector<KeyPoint> target_keypoints__;

    public:
        DescriptorMatch();
        DescriptorMatch(const Mat& image, 
                        const char* keypoint_type, 
                        const char* descriptor_type, 
                        const char* matcher_type);
        ~DescriptorMatch();


        //setters
        void setReferenceImage(const Mat& image);
        void setMatcher(const char* matcher_type);
        void setDescriptors(const char* descriptor_type);
        
        //getters
        const Mat& getReferenceImage();
        const vector<KeyPoint>& getKeypoints();
        const Mat& getDescriptors();
        const vector<cv::DMatch>& getMatches();

        void setMatches(const Mat& target_image);

        //displayers
        void displayMatches();
        void displayKeypoints();
        
};
#endif //DESCRIPTORMATCH_H

