#ifndef BAGOFWORDS_H
#define BAGOFWORDS_H

#include <opencv2/features2d/features2d.hpp>

using namespace cv;
using namespace std;

class BagOfWords{
    private:
        vector<Mat> data_;
        string data_path_;

        Ptr<FeatureDetector> featureDetector;
        Ptr<DescriptorExtractor> descExtractor;
        Ptr<DescriptorMatcher> descMatcher;
        Ptr<BOWImgDescriptorExtractor> bowExtractor;

        int dictionary_size_; //number of features per image 
    
        Mat descriptors_;
        Mat vocabulary_;
        //Mat training_data_; 

    public:
        BagOfWords();
        ~BagOfWords();
    
        //Default functions using pre-set parameters
        Mat computeDescriptors(vector<Mat>); 
        Mat computeVocabulary();
        Mat computeCodewords(vector<Mat>);
        
        //to-do: add getters and setters
        //void setDescriptors();
        //void setVocabulary();
        
};
#endif //BAGOFWORDS_H

