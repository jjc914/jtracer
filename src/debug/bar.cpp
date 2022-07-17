//
//  bar.cpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 26/6/2022.
//

#include "bar.hpp"

namespace debug {

    bar::bar() {
        std::cout << "[-------------------------------------------------] 0%" << std::flush;
    }

    void bar::print() {
        int steps = round(progress * 49.0);
        if (steps > roundedSteps) {
            int percentage = round((double)steps * (100.0 / 49.0));
            std::cout << "\r[" << std::string(steps, '#') << std::string(49 - steps, '-') << "] " << percentage << "%" << std::flush;
        }
        if (progress >= 1.0 - __DBL_EPSILON__) {
            std::cout << "]" << std::endl;;
        }
        roundedSteps = steps;
    }

    void bar::setProgress(const double progress) {
        this->progress = progress;
    }

    double bar::getProgress() const {
        return progress;
    }
}
