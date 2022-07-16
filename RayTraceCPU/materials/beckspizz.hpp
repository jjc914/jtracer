//
//  beckspizz.hpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 14/7/2022.
//

#ifndef beckspizz_hpp
#define beckspizz_hpp

#include "brdf.hpp"
#include "math.hpp"

namespace materials {

    class beckspizz : public brdf { //TODO: Oren-Nayar microfacet reflection
    public:
        beckspizz(const color diffuseColor, const double alphax, const double alphay, const color emissionColor = color(0.0, 0.0, 0.0), const double emissionPower = 0.0);
        
        vec3<double> sampleBounceDirection(vec3<double> inDirection, vec3<double> normal) const;
    private:
//        double 
    };
}

#endif /* beckspizz_hpp */
