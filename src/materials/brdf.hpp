#ifndef brdf_hpp
#define brdf_hpp

#include "math/color.hpp"
#include "math/vec3.hpp"

using namespace math;

namespace materials {

    class brdf {
    public:
        brdf(const color albedo, const color emissionColor = color(0.0, 0.0, 0.0), const double emissionPower = 0.0);
        
        virtual color evaluate(vec3<double> wo, vec3<double> wi) const = 0;
        
        color getAlbedo() const;
        color getEmissionColor() const;
        double getEmissionPower() const;
    private:
        color albedo;
        color emissionColor;
        double emissionPower;
    };
}

#endif
