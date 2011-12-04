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
        Keypoints *keypoints_;
        Descriptors descriptors_;
        const char* keypoint_type_;
        const char* descriptor_type_;
        const char* matcher_type_;

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
        void displayMatches(const Mat& target_image);
        void displayKeypoints();
        
};
#endif //DESCRIPTORMATCH_H

