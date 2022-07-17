//
//  primative.cpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 24/3/2022.
//

#include "primative.hpp"

namespace primatives {
    primative::primative(const std::string name, brdf* mat, const vec3<double> position) : name(name), mat(mat), position(position) {
    }

    std::string primative::getName() const {
        return name;
    }

    brdf* primative::getMaterial() const {
        return mat;
    }

    vec3<double> primative::getPosition() const {
        return position;
    }
}
