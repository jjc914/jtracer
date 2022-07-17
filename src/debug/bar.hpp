//
//  bar.hpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 26/6/2022.
//

#ifndef bar_hpp
#define bar_hpp

#include <iostream>
#include <string>

#include "../math/math.hpp"

namespace debug {

    class bar {
    public:
        bar();
        
        void print();
        
        double getProgress() const;
        
        void setProgress(const double progress);
    private:
        double progress;
        int roundedSteps;
    };
}

#endif /* bar_hpp */
