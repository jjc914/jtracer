#include "lambertian.hpp"

namespace materials {

    lambertian::lambertian(const color albedo, const color emissionColor, const double emissionPower) : brdf(albedo, emissionColor, emissionPower) {
    }

    color lambertian::evaluate(vec3<double> wo, vec3<double> wi) const {
        return getAlbedo();
    }
}
