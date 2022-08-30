#ifndef fresnel_hpp
#define fresnel_hpp

#include "math/vec3.hpp"

using namespace math;

namespace materials {

    // fresnel reflectance between dielectric and conductor
    // TODO: add dielectric and dielectric
    class fresnel {
    public:
        double evaluate(const vec3<double> wi, const vec3<double> wn) const;
    private:
    };
}

#endif