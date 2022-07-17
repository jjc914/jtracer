//
//  lambertian.hpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 14/7/2022.
//

#ifndef lambertian_hpp
#define lambertian_hpp

#include "brdf.hpp"
#include "math/math.hpp"

using namespace math;

namespace materials {

    class lambertian : public brdf { //TODO: Oren-Nayar microfacet reflection
    public:
        lambertian(const color diffuseColor, const color emissionColor = color(0.0, 0.0, 0.0), const double emissionPower = 0.0);
        
        vec3<double> sampleBounceDirection(vec3<double> inDirection, vec3<double> normal) const;
    };
}

#endif /* lambertian_hpp */
