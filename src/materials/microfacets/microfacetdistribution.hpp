#ifndef microfacetdistribution_hpp
#define microfacetdistribution_hpp

#include "math/vec3.hpp"

using namespace math;

namespace materials {

    class microfacetdistribution {
    public:
        virtual double d(const vec3<double> wh) const = 0;
        virtual double l(const vec3<double> w, const vec3<double> wh) const = 0;
        virtual double g1(const vec3<double> w, const vec3<double> wh) const = 0;
        virtual double g(const vec3<double> wo, const vec3<double> wi) const = 0;
    };
}

#endif