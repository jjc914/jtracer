//
//  primative.cpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 24/3/2022.
//

#include "primative.hpp"

namespace primatives {
    primative::primative(std::string name, vec3<double> position, color pColor) : name(name), position(position), pColor(pColor) {
    }

    std::string primative::getName() const {
        return name;
    }

    vec3<double> primative::getPosition() const {
        return position;
    }

    color primative::getColor() const {
        return pColor;
    }
}
