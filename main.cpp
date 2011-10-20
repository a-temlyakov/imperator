#include "color/ColorMatch.h"
//#include "feature/DescriptorMatch.h"
//#include "feature/Keypoints.h"
//#include "feature/Descriptors.h"
#include "training/BagOfWords.h"
#include <opencv2/opencv.hpp>

#include <iostream>

int main(int argc, char** argv)
{
    using std::cout;
    using std::endl;
    using namespace cv;
    
    if(argc != 4)
    {
        cout << "Must input 2 images to match" << endl;
        cout << "Example: ./main path_to_img1 path_to_img2 " << endl;

        return -1;
    }

    //cv::Mat image1 = cv::imread(argv[1]);
    //cv::Mat image2 = cv::imread(argv[2]);

    /*if(!image1.data || !image2.data)
    {
        cout << "Unable to load image!" << endl;
        return -1;
    }*/
    
    //ColorMatch c(32);
    //c.setReferenceImage(image1);

    //double distance = c.compare(image2);
    //cout << "Color Distance: " << distance << endl;
    
    //DescriptorMatch d(image1, "FAST", "SURF", "FlannBased");
    //d.displayKeypoints();
    //d.setMatches(image2);
    //d.displayMatches(image2);

    //Keypoints k(image1, "FAST");
    //cout << k.size() << " keypoints found." << endl;
    //k.displayKeypoints();
    //
    //return 1;

    //Descriptors d(image1, k.getKeypoints(), "SURF");
    //Mat desc = d.getDescriptors();
   
    cout << "---\t BUILD VOCAB\t ---" << endl;
    //cout << d.getDescriptorSize() << endl;
    //cout << d.getDescriptorType() << endl;
    
    //SurfFeatureDetector detector(400);
    /*FastFeatureDetector detector(30);
    vector<KeyPoint> keypoints;
    Ptr<DescriptorExtractor > extractor(
        new OpponentColorDescriptorExtractor(
            Ptr<DescriptorExtractor>(new SurfDescriptorExtractor())
            )
        );

    Mat desc;

    cout << extractor->descriptorSize() << endl;
    cout << extractor->descriptorType() << endl;
    
    Mat t_descriptors(1, 
                            extractor->descriptorSize(), 
                            extractor->descriptorType());

    
    
    for(int i=1; i < 3; i++)
    {
        Mat img = imread(argv[i]);
        detector.detect(img, keypoints);
        extractor->compute(img, keypoints, desc);

        t_descriptors.push_back(desc);
    }
    */

    //Mat t = imread(argv[1]);

    //cout << t << endl;
   
    //if(t.empty())
    //{
    //    cout << "EMPTY!" << endl;
    // }

    std::vector<Mat> data;
    for(int i=1; i < 3; i++)
    {
        Mat img = imread(argv[i]);
        data.push_back(img);
    }
    
    BagOfWords bow;
    Mat training_descriptors = bow.computeDescriptors(data);

    cout << "Total descriptors: " << training_descriptors.rows << endl;

    Mat vocab = bow.computeVocabulary();
    //cout << vocab << endl;
    Mat training_data = bow.computeCodewords(data);    

    //cout << training_data << endl;
    //int dictSize = 15;
    /*BOWKMeansTrainer bowtrainer(dictSize); //num clusters
    bowtrainer.add(training_descriptors);
    Mat vocab = bowtrainer.cluster();
    */

    /*cout << "Vocab rows: " << vocab.rows << endl;
    cout << "Vocab cols: " << vocab.cols << endl;

    cout << "---\t TRAIN BOW\t ---" << endl;
    Ptr<FeatureDetector > detector2(new FastFeatureDetector());
    Ptr<DescriptorExtractor > extractor2(
        new OpponentColorDescriptorExtractor(
           Ptr<DescriptorExtractor>(new SurfDescriptorExtractor())
           )
        );

    Ptr<DescriptorMatcher > matcher(new BruteForceMatcher<L2<float> >());

    BOWImgDescriptorExtractor bowide(extractor2, matcher);
    bowide.setVocabulary(vocab);

    vector<KeyPoint> keypoints2;
    Mat labels(0, 1, CV_32FC1);
    Mat training_data(0, dictSize, CV_32FC1);
    Mat response_hist;
    for(int i=1; i < 3; i++)
    {
        Mat img2 = imread(argv[i]);
        detector2->detect(img2, keypoints2);
        bowide.compute(img2, keypoints2, response_hist);
    
        training_data.push_back(response_hist);
        labels.push_back((float) 1);
    }
    */
    cout << "Rows: " << training_data.rows << endl;
    cout << "Cols: " << training_data.cols << endl;

    /*for(int i = 0; i < training_data.rows; i++)
    {
        for(int j = 0; j < training_data.cols; j++)
        {
            cout << training_data.at<float>(i,j) << ' ';
        }
        cout << '\n';
    }*/

    /*** BEGIN SVM ***/
    
    CvSVMParams params;
    params.svm_type = CvSVM::ONE_CLASS;
    params.kernel_type = CvSVM::RBF;
    //params.svm_type = CvSVM::C_SVC;
    params.gamma = 500;
    params.nu = 0.0001;
    //params.C = 100.0;
    params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 100, 0.000001);

    CvSVM svm;

    svm.train(training_data, cv::Mat(), cv::Mat(), cv::Mat(), params);
   
    vector<Mat> t_data;
    t_data.push_back(imread(argv[3]));
    Mat target_data = bow.computeCodewords(t_data);

    //cout << target_data << endl;

    /*
    vector<KeyPoint> keypoints3;
    Mat response_hist2;
    
    Mat img3 = imread(argv[3]);
    detector2->detect(img3, keypoints3);
    bowide.compute(img3, keypoints3, response_hist2);
    */

    float response = svm.predict(target_data);

    cout << "Response: " << response << endl;
    
    return 1;
}
