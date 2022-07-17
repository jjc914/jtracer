//
//  brdf.hpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 25/6/2022.
//

#ifndef brdf_hpp
#define brdf_hpp

#include "math/color.hpp"
#include "math/vec3.hpp"

using namespace math;

namespace materials {

    class brdf {
    public:
        brdf(const color diffuseColor, const color emissionColor = color(0.0, 0.0, 0.0), const double emissionPower = 0.0);
        
        virtual vec3<double> sampleBounceDirection(vec3<double> inDirection, vec3<double> normal) const = 0;
        
        color getDiffuseColor() const;
        color getEmissionColor() const;
        double getEmissionPower() const;
    private:
        color diffuseColor;
        color emissionColor;
        double emissionPower;
    };
}

#endif /* brdf_hpp */
