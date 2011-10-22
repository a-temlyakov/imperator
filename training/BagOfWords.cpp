#include "BagOfWords.h"
#include <iostream>

BagOfWords::BagOfWords()
{
    dictionary_size_ = 25;

    featureDetector = FeatureDetector::create("SIFT");
    descExtractor = DescriptorExtractor::create("OpponentSIFT");
    descMatcher = DescriptorMatcher::create("BruteForce");
    bowExtractor = new BOWImgDescriptorExtractor(descExtractor, descMatcher);

    descriptors_.create(0,
                        descExtractor->descriptorSize(),
                        descExtractor->descriptorType());
}

BagOfWords::~BagOfWords()
{

}

Mat BagOfWords::computeDescriptors(vector<Mat> training_data)
{
    Mat descriptor;
    vector<KeyPoint> keypoints;

    for(unsigned int i = 0; i < training_data.size(); i++)
    {
        featureDetector->detect(training_data.at(i), keypoints);

        if(keypoints.size() == 0)
        {   //no keypoints found
            continue;
        }

        descExtractor->compute(training_data.at(i), keypoints, descriptor);
        descriptors_.push_back(descriptor);
    }

    return descriptors_;
}

Mat BagOfWords::computeVocabulary()
{
    if(descriptors_.empty())
    {
        //to-do: throw error
    }
    
    TermCriteria tc(CV_TERMCRIT_ITER, 100, 0.0001);
    int retries = 5;
    int flags = KMEANS_PP_CENTERS;

    BOWKMeansTrainer bowtrainer(dictionary_size_, tc, retries, flags);
    bowtrainer.add(descriptors_);
    vocabulary_ = bowtrainer.cluster();
    
    bowExtractor->setVocabulary(vocabulary_);

    return vocabulary_;
}

Mat BagOfWords::computeCodewords(vector<Mat> data)
{
    Mat response_hist;
    Mat codewords(0, dictionary_size_, CV_32FC1);
    vector<KeyPoint> keypoints;

    for(unsigned int i = 0; i < data.size(); i++)
    {
        featureDetector->detect(data.at(i), keypoints);    
        bowExtractor->compute(data.at(i), keypoints, response_hist);

        codewords.push_back(response_hist);
    }

    return codewords;
}
