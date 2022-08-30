#include "beckmannspizzichino.hpp"

namespace materials {

    beckmannspizzichino::beckmannspizzichino(double ax, double ay) : ax(ax), ay(ay) {
    }

    double beckmannspizzichino::d(const vec3<double> wh) const {
        double t = tan2Zenith(wh);
        if (std::isinf(t)) return 0.0;
        double e = std::exp(-t * (cos2Azimuth(wh) / (ax * ax) + sin2Azimuth(wh) / (ay * ay)));
        return e / (M_PI * ax * ay * cos2Zenith(wh) * cos2Zenith(wh));
    }

    double beckmannspizzichino::l(const vec3<double> w, const vec3<double> wh) const {
        double absTanZenith = std::abs(tanZenith(w));
        if (std::isinf(absTanZenith)) return 0.0;
        double alpha = std::sqrt(cos2Azimuth(w) * ax * ax + sin2Azimuth(w) * ay * ay);
        double a = 1 / (alpha * absTanZenith);
        if (a > 1.6) return 0.0;
        return (1.0 - 1.259 * a + 0.386 * a * a) / 
               (3.535 * a + 2.181 * a * a);
    }

    double beckmannspizzichino::g1(const vec3<double> w, const vec3<double> wh) const {
        return 1 / (1 + l(w));
    }

    double beckmannspizzichino::g(const vec3<double> wo, const vec3<double> wi) const {
        return 1 / (1 + l(wo) + l(wi));
    }
}