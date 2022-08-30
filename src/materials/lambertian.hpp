#ifndef lambertian_hpp
#define lambertian_hpp

#include "brdf.hpp"
#include "math/math.hpp"

using namespace math;

namespace materials {

    class lambertian : public brdf { //TODO: Oren-Nayar microfacet reflection
    public:
        lambertian(const color albedo, const color emissionColor = color(0.0, 0.0, 0.0), const double emissionPower = 0.0);
        
        color evaluate(vec3<double> wo, vec3<double> wi) const;
    };
}

#endif
