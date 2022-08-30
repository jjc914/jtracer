#ifndef beckmannspizzichino_hpp
#define beckmannspizzichino_hpp

#include "microfacetdistribution.hpp"
#include "math/math.hpp"

using namespace math;

namespace materials {

    class beckmannspizzichino : public microfacetdistribution {
    public:
        beckmannspizzichino(double ax, double ay);

        double d(const vec3<double> wh) const;
        double l(const vec3<double> w, const vec3<double> wh = vec3<double>()) const;
        double g1(const vec3<double> w, const vec3<double> wh = vec3<double>()) const;
        double g(const vec3<double> wo, const vec3<double> wi) const;
    private:
        double ax, ay;
    };
}

#endif