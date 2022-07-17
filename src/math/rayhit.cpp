//
//  rayhit.cpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 26/3/2022.
//

#include "rayhit.hpp"

namespace math {

    rayhit::rayhit() {
    }

    rayhit::rayhit(std::string name, vec3<double> position, vec3<double> normal, primative* prim) : name(name), position(position), normal(normal), prim(prim) {
    }
}
