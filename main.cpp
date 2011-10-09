#include "color/ColorMatch.h"
#include "feature/DescriptorMatch.h"
//#include "feature/Keypoints.h"
//#include "feature/Descriptors.h"
#include <iostream>

int main(int argc, char** argv)
{
    using std::cout;
    using std::endl;

    if(argc != 3)
    {
        cout << "Must input 2 images to match" << endl;
        cout << "Example: ./main path_to_img1 path_to_img2 " << endl;

        return -1;
    }

    cv::Mat image1 = cv::imread(argv[1]);
    cv::Mat image2 = cv::imread(argv[2]);

    if(!image1.data || !image2.data)
    {
        cout << "Unable to load image!" << endl;
        return -1;
    }
    
    ColorMatch c(32);
    c.setReferenceImage(image1);

    double distance = c.compare(image2);
    cout << "Color Distance: " << distance << endl;
    
    DescriptorMatch d(image1, "FAST", "SURF", "FlannBased");
    //d.displayKeypoints();
    d.setMatches(image2);
    //d.displayMatches(image2);

    /***    TEMPLATE MATCHING   ***/
    cv::Mat result;
    cv::matchTemplate(image1, image2, result, CV_TM_CCOEFF_NORMED);

    double minval, maxval;
    cv::Point minloc, maxloc;
    cv::minMaxLoc(result, &minval, &maxval, &minloc, &maxloc);
    cout << "Min val: " << minval << endl;
    cout << "Max val: " << maxval << endl;

    
    cv::rectangle(image1, 
                  cv::Point(minloc.x, minloc.y),
                  cv::Point(minloc.x + image2.cols, minloc.y + image2.rows),
                  cv::Scalar(0,0,255,0), 1, 0, 0);

    
    cv::namedWindow("reference");
    cv::imshow("reference", image1);
    cv::waitKey(0);

    cv::namedWindow("target");
    cv::imshow("target", image2); 
    cv::waitKey(0);

    
/*
    Keypoints k(image1, "FAST");
    cout << k.size() << " keypoints found." << endl;
    k.displayKeypoints();

    Descriptors dd(image1, k.getKeypoints(), "SURF");
    cv::Mat desc = dd.getDescriptors();
*/
    return 1;
}
