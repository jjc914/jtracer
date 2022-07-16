//
//  bar.cpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 26/6/2022.
//

#include "bar.hpp"

namespace debug {

    bar::bar() {
        std::cout << "         20%       40%       60%       80%" << std::endl;
        std::cout << "[---------|---------|---------|---------|---------]" << std::endl;
        std::cout << "[";
    }

    void bar::print() {
        int percentage = round(progress * 49.0);
        if (percentage > roundedPercentage) {
            std::cout << "*";
        }
        if (progress >= 1.0 - __DBL_EPSILON__) {
            std::cout << "]" << std::endl;;
        }
        roundedPercentage = percentage;
    }

    void bar::setProgress(const double progress) {
        this->progress = progress;
    }

    double bar::getProgress() const {
        return progress;
    }
}
