//
//  beckspizz.cpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 14/7/2022.
//

#include "beckspizz.hpp"

namespace materials {

    beckspizz::beckspizz(const color diffuseColor, const double alphax, const double alphay, const color emissionColor, const double emissionPower) : brdf(diffuseColor, emissionColor, emissionPower) {
    }

    vec3<double> beckspizz::sampleBounceDirection(vec3<double> inDirection, vec3<double> normal) const {
        return math::rejectionSampleHemisphere(normal);
    }
}
