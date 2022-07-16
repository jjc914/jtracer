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

#include "primatives.hpp"

using namespace primatives;

namespace math {

    struct rayhit {
        rayhit();
        rayhit(std::string name, vec3<double> position, vec3<double> normal, primative* prim);
        
        std::string name;
        vec3<double> position;
        vec3<double> normal;
        primatives::primative* prim;
    };
}

#endif /* rayhit_hpp */
