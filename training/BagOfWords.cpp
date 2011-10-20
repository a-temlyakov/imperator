#include "BagOfWords.h"

BagOfWords::BagOfWords()
{
    dictionary_size_ = 5;

    featureDetector = FeatureDetector::create("FAST");
    descExtractor = DescriptorExtractor::create("SURF");

    training_data_.create(0, dictionary_size_, CV_32FC1);
    descriptors_.create(1,
                        descExtractor->descriptorSize(),
                        descExtractor->descriptorType());
}

BagOfWords::~BagOfWords()
{

}

Mat BagOfWords::computeDescriptors(vector<Mat> data)
{
    Mat descriptor;
    vector<KeyPoint> keypoints;

    for(unsigned int i = 0; i < data.size(); i++)
    {
        featureDetector->detect(data.at(i), keypoints);
        descExtractor->compute(data.at(i), keypoints, descriptor);
    
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

    return vocabulary_;
}

Mat BagOfWords::computeTrainingData(vector<Mat> data)
{
    if(vocabulary_.empty())
    {
        //to-do: throw error
    }

    Mat response_hist;
    vector<KeyPoint> keypoints;
    
    Ptr<DescriptorMatcher> matcher(new BruteForceMatcher<L2<float> >());

    BOWImgDescriptorExtractor bowide(descExtractor, matcher);
    bowide.setVocabulary(vocabulary_);

    for(unsigned int i = 0; i < data.size(); i++)
    {
        featureDetector->detect(data.at(i), keypoints);    
        bowide.compute(data.at(i), keypoints, response_hist);

        training_data_.push_back(response_hist);
    }

    return training_data_;
}
