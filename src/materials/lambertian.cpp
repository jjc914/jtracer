//
//  lambertian.cpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 14/7/2022.
//

#include "lambertian.hpp"

namespace materials {

    lambertian::lambertian(const color diffuseColor, const color emissionColor, const double emissionPower) : brdf(diffuseColor, emissionColor, emissionPower) {
    }

    vec3<double> lambertian::sampleBounceDirection(vec3<double> inDirection, vec3<double> normal) const {
        return math::rejectionSampleHemisphere(normal);
    }
}
