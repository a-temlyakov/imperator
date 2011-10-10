#ifndef DESCRIPTORMATCH_H
#define DESCRIPTORMATCH_H

#include <opencv2/features2d/features2d.hpp>
#include "Keypoints.h"
#include "Descriptors.h"

class DescriptorMatch{
    private:
        cv::Mat reference_image;
        cv::Ptr<cv::DescriptorMatcher> matcher;
        std::vector<cv::DMatch> matches;
        Keypoints keypoints;
        Descriptors descriptors;
        const char* matcher_type;
        const char* keypoint_type;
        const char* descriptor_type;

    public:
        DescriptorMatch();
        DescriptorMatch(cv::Mat&, const char*, const char*, const char*);
        ~DescriptorMatch();

        void setReferenceImage(cv::Mat&);
        void setMatcher(const char*);
        void setKeypoints(const char*);
        void setDescriptors(const char*);
        
        cv::Mat getReferenceImage();
        std::vector<cv::KeyPoint> getKeypoints();
        cv::Mat getDescriptors();
        std::vector<cv::DMatch> getMatches();

        void setMatches(cv::Mat&);

        void displayMatches(cv::Mat&);
        void displayKeypoints();
        
};

#endif //DESCRIPTORMATCH_H
