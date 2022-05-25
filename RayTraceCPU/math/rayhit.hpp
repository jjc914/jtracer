//
//  rayhit.hpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 26/3/2022.
//

#ifndef rayhit_hpp
#define rayhit_hpp

#include "vec3.hpp"
#include "color.hpp"

namespace math {

    struct rayhit {
        rayhit();
        rayhit(std::string name, vec3<double> position, vec3<double> normal, color pColor);
        
        std::string name;
        vec3<double> position;
        vec3<double> normal;
        color pColor;
    };
}

#endif /* rayhit_hpp */
