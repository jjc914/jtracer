//
//  ray.cpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 22/3/2022.
//

#include "ray.hpp"
#include <iostream>

namespace math {

    ray::ray(vec3<double> origin, vec3<double> direction) : origin(origin), direction(direction){
        this->direction.normalize();
    }

    vec3<double> ray::getOrigin() const {
        return origin;
    }

    vec3<double> ray::getDirection() const {
        return direction;
    }
}
