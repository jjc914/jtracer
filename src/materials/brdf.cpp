#include "brdf.hpp"

namespace materials {

    brdf::brdf(const color albedo, const color emissionColor, const double emissionPower) : albedo(albedo), emissionColor(emissionColor), emissionPower(emissionPower) {
    }

    color brdf::getAlbedo() const {
        return albedo;
    }

    color brdf::getEmissionColor() const {
        return emissionColor;
    }

    double brdf::getEmissionPower() const {
        return emissionPower;
    }
}
