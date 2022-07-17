//
//  brdf.cpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 25/6/2022.
//

#include "brdf.hpp"

namespace materials {

    brdf::brdf(const color diffuseColor, const color emissionColor, const double emissionPower) : diffuseColor(diffuseColor), emissionColor(emissionColor), emissionPower(emissionPower) {
    }

    color brdf::getDiffuseColor() const {
        return diffuseColor;
    }

    color brdf::getEmissionColor() const {
        return emissionColor;
    }

    double brdf::getEmissionPower() const {
        return emissionPower;
    }
}
