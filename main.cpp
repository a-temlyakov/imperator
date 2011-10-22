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
        cout << "Must input 3 images to match" << endl;

        return -1;
    }

    cout << "---\t BUILD VOCAB\t ---" << endl;
    
    std::vector<Mat> data;
    for(unsigned int i = 1; i < 3; i++)
    {
        Mat img = imread(argv[i]);
        data.push_back(img);
    }

    BagOfWords bow;
    Mat training_descriptors = bow.computeDescriptors(data);
    
    cout << "Total descriptors: " << training_descriptors.rows << endl;

    Mat vocab = bow.computeVocabulary();
    Mat training_data = bow.computeCodewords(data);    

    cout << "Cols: " << training_data.cols << endl;
    cout << "Training data: " << endl;
    cout << training_data << endl;

    /*** BEGIN SVM ***/
    CvSVMParams params;
    params.svm_type = CvSVM::ONE_CLASS;
    params.kernel_type = CvSVM::RBF;
    params.nu = 0.5;
    params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 100, 0.000001);

    CvSVM svm;

    svm.train_auto(training_data, cv::Mat(), cv::Mat(), cv::Mat(), params);
   
    vector<Mat> t_data;
    t_data.push_back(imread(argv[3]));
    Mat target_data = bow.computeCodewords(t_data);

    cout << "Target data: " << endl;
    cout << target_data << endl;

    float response = svm.predict(target_data);

    cout << "Response: " << response << endl;
    
    return 1;
}
