#include "BagOfWords.h"
#include <iostream>

BagOfWords::BagOfWords()
{
    dictionary_size_ = 1000;

    featureDetector = FeatureDetector::create("SIFT");
    descExtractor = DescriptorExtractor::create("SIFT");
    descMatcher = DescriptorMatcher::create("BruteForce");
    bowExtractor = new BOWImgDescriptorExtractor(descExtractor, descMatcher);

    descriptors_.create(0,
                        descExtractor->descriptorSize(),
                        descExtractor->descriptorType());

    codewords_.create(0, dictionary_size_, CV_32FC1);
}

BagOfWords::BagOfWords(int dict_size,
//As of 11/2011:
// Features: FAST, STAR, SIFT, SURF, MSER, GFTT, HARRIS, ORB
// Descriptors: SURF, OpponentSURF, SIFT, OpponentSIFT, BRIEF, ORB
// Matchers: BruteForce, BruteForce-L1, FlannBased, BruteForce-Hamming,
//           BruteForce-HammingLUT
                       const char* feature_name,
                       const char* descriptor_name,
                       const char* matcher_name)
{
    dictionary_size_ = dict_size;
    featureDetector = FeatureDetector::create(feature_name);
    descExtractor = DescriptorExtractor::create(descriptor_name);
    descMatcher = DescriptorMatcher::create(matcher_name);
    bowExtractor = new BOWImgDescriptorExtractor(descExtractor, descMatcher);

    descriptors_.create(0,
                       descExtractor->descriptorSize(),
                       descExtractor->descriptorType());

    codewords_.create(0, dictionary_size_, CV_32FC1);
}

BagOfWords::~BagOfWords()
{

}

void BagOfWords::setDictionarySize(int dict_size)
{
    dictionary_size_ = dict_size;
}

void BagOfWords::setDescriptors(Mat descriptors)
{
    descriptors_ = descriptors;
}

void BagOfWords::setVocabulary(Mat vocabulary)
{
    vocabulary_ = vocabulary;
    bowExtractor->setVocabulary(vocabulary_);
}

void BagOfWords::setFeatureDetector(const char* feature_name)
{
    featureDetector = FeatureDetector::create(feature_name);
}

void BagOfWords::setDescriptorExtractor(const char* descriptor_name)
{
    descExtractor = DescriptorExtractor::create(descriptor_name);

    //generate new bowExtractor with updated descriptor extractor
    //descriptor matcher must have at least default initialization
    bowExtractor = new BOWImgDescriptorExtractor(descExtractor, descMatcher);
}

void BagOfWords::setDescriptorMatcher(const char* matcher_name)
{
    descMatcher = DescriptorMatcher::create(matcher_name);

    //generate new bowExtractor with updated descriptor matcher
    //descriptor extractor must have at least default initialization
    bowExtractor = new BOWImgDescriptorExtractor(descExtractor, descMatcher);
}

int BagOfWords::getDictionarySize()
{
    return dictionary_size_;
}

Mat BagOfWords::getDescriptors()
{
    return descriptors_;
}

Mat BagOfWords::getVocabulary()
{
    return vocabulary_;
}

Mat BagOfWords::getCodewords()
{
    return codewords_;
}

void BagOfWords::saveDescriptors(string file_name, string description)
{
    FileStorage fs(file_name, FileStorage::WRITE);
    fs << description << descriptors_;
    fs.release();
}

void BagOfWords::saveVocabulary(string file_name, string description)
{
    FileStorage fs(file_name, FileStorage::WRITE);
    fs << description << vocabulary_;
    fs.release();
}

void BagOfWords::saveCodewords(string file_name, string description)
{
    FileStorage fs(file_name, FileStorage::WRITE);
    fs << description << codewords_;
    fs.release();
}    

void BagOfWords::loadDescriptors(string file_name, string description)
{
    FileStorage fs(file_name, FileStorage::READ);
    fs[description] >> descriptors_;
    fs.release();
}

void BagOfWords::loadVocabulary(string file_name, string description)
{
    FileStorage fs(file_name, FileStorage::READ);
    fs[description] >> vocabulary_;
    fs.release();

    bowExtractor->setVocabulary(vocabulary_);
}

void BagOfWords::loadCodewords(string file_name, 
                               string description, 
                               Mat &codewords)
{
    FileStorage fs(file_name, FileStorage::READ);
    fs[description] >> codewords;
    fs.release();
}

int BagOfWords::computeDescriptors(vector<string> file_list)
{
    Mat descriptor, image;
    vector<KeyPoint> keypoints;

    for(unsigned int i = 0; i < file_list.size(); i++)
    {
        //to-do: throw error if image is grayscale (one channel),
        //       but descriptor is OpponentSIFT (or OpponentSURF)
        cout << ".";
        cout.flush();
        
        image = imread(file_list.at(i));
        if(!image.data)
            continue;
        
        featureDetector->detect(image, keypoints);

        if(keypoints.size() == 0) //no keypoints found
            continue;
        
        descExtractor->compute(image, keypoints, descriptor);
        descriptors_.push_back(descriptor);
    }
   
    cout << "\n";
    return EXIT_SUCCESS;
}

int BagOfWords::computeVocabulary()
{
    if(descriptors_.empty())
    {
        return EXIT_FAILURE;
    }
    
    TermCriteria tc(CV_TERMCRIT_ITER, 100, 0.0001);
    int retries = 5;
    int flags = KMEANS_PP_CENTERS;

    BOWKMeansTrainer bowtrainer(dictionary_size_, tc, retries, flags);
    bowtrainer.add(descriptors_);
    vocabulary_ = bowtrainer.cluster();
    
    bowExtractor->setVocabulary(vocabulary_);

    return EXIT_SUCCESS;
}

int BagOfWords::computeCodewords(vector<string> data, Mat &codewords)
{
    if(vocabulary_.empty())
    {
        computeDescriptors(data);
        computeVocabulary();
    }

    Mat response_hist, image;
    vector<KeyPoint> keypoints;

    for(unsigned int i = 0; i < data.size(); i++)
    {
        image = imread(data.at(i));

        if(!image.data)
            continue;
        
        featureDetector->detect(image, keypoints);    
        bowExtractor->compute(image, keypoints, response_hist);

        codewords_.push_back(response_hist);
    }

    return EXIT_SUCCESS;
}
