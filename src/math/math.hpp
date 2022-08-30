#ifndef math_hpp
#define math_hpp

#define _USE_MATH_DEFINES
#include <math.h>
#include <tuple>

#include "vec2.hpp"
#include "vec3.hpp"
#include "mat3x3.hpp"

namespace math {

    double rad2deg(const double rad);
    double deg2rad(const double deg);
    vec3<double> rejectionSampleSphere();
    vec3<double> rejectionSampleHemisphere(const vec3<double> normal);
    std::tuple<unsigned int, double, double> solveQuadratic(const double a, const double b, const double c);
    double riemannSum(double (*func)(double), const double a, const double b, const int samples);
    
    double sinAzimuth(const vec3<double> w);
    double sin2Azimuth(const vec3<double> w);
    double cosAzimuth(const vec3<double> w);
    double cos2Azimuth(const vec3<double> w);
    double tanAzimuth(const vec3<double> w);
    double tan2Azimuth(const vec3<double> w);

    double sinZenith(const vec3<double> w);
    double sin2Zenith(const vec3<double> w);
    double cosZenith(const vec3<double> w);
    double cos2Zenith(const vec3<double> w);
    double tanZenith(const vec3<double> w);
    double tan2Zenith(const vec3<double> w);

    template<typename T>
    T min(const T a, const T b) {
        return a < b ? a : b;
    }

    template<typename T>
    T max(const T a, const T b) {
        return a > b ? a : b;
    }

    template<typename T>
    T clamp(const T val, const T min, const T max) {
        return val < min ? min : (val > max ? max : val);
    }

    template<typename T>
    T randRange(const T min, const T max) {
        return (T)(min + (rand() / (double)RAND_MAX) * (max - min));
    }

    template<typename T>
    int roundAwayFromZero(const T val) {
        if (val > 0) {
            return ceil(val);
        } else {
            return floor(val);
        }
    }
}

#endif
