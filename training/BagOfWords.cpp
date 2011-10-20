#include "BagOfWords.h"

BagOfWords::BagOfWords()
{
    dictionary_size_ = 100;

    featureDetector = FeatureDetector::create("FAST");
    descExtractor = DescriptorExtractor::create("SURF");
    descMatcher = DescriptorMatcher::create("BruteForce");
    bowExtractor = new BOWImgDescriptorExtractor(descExtractor, descMatcher);

    descriptors_.create(1,
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

    BOWKMeansTrainer bowtrainer(dictionary_size_);
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
