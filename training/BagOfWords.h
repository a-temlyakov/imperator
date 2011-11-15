#ifndef BAGOFWORDS_H
#define BAGOFWORDS_H

#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>

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
        Mat codewords_;

    public:
        BagOfWords();
        BagOfWords(int, const char*, const char*, const char*);
        ~BagOfWords();
    
        //computers :)
        //Descriptors and vocabulary are built during training phase
        //Codewords are used during testing and training
        int computeDescriptors(vector<string>); 
        int computeVocabulary();
        int computeCodewords(vector<string>, Mat&);
        
        //setters
        void setDictionarySize(int);
        void setDescriptors(Mat);
        void setVocabulary(Mat);
        void setFeatureDetector(const char*);
        void setDescriptorExtractor(const char*);
        void setDescriptorMatcher(const char*);

        //getters
        int getDictionarySize();
        Mat getDescriptors();
        Mat getVocabulary();
        Mat getCodewords();

        //savers
        void saveDescriptors(string, string);
        void saveVocabulary(string, string);
        void saveCodewords(string, string);
    
        //loaders
        void loadDescriptors(string, string);
        void loadVocabulary(string, string);
        static void loadCodewords(string, string, Mat&);
};
#endif //BAGOFWORDS_H

