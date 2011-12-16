#ifndef COLORMATCH_H
#define COLORMATCH_H

#include "ColorHistogram.h"

class ColorMatch{
    private:
        MatND reference_hist_;
        MatND target_hist_;
        ColorHistogram hist_;

    public:
        ColorMatch();
        ColorMatch(int num_bins);
        ~ColorMatch();

        void setReferenceImage(const Mat& image);
        double compare(const Mat& target_image);
};
#endif //COLORMATCH_H

