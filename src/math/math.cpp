#include "math.hpp"

namespace math {

    double rad2deg(const double rad) {
        return rad * (180 / M_PI);
    }

    double deg2rad(const double deg) {
        return deg * (M_PI / 180);
    }

    vec3<double> rejectionSampleSphere() {
        // TODO: should choose sample on surface of sphere
        double radius = 1.0;
        vec3<double> vec;
        do {
            vec = vec3<double>(randRange(-1.0, 1.0), randRange(-1.0, 1.0), randRange(-1.0, 1.0));
        } while (vec.getMagnitude() > radius);
        return vec;
    }

    vec3<double> rejectionSampleHemisphere(const vec3<double> normal) {
        vec3<double> vec = rejectionSampleSphere();
        if (vec3<double>::dot(vec, normal) < 0) {
            vec *= -1.0;
        }
        return vec;
    }

    std::tuple<unsigned int, double, double> solveQuadratic(const double a, const double b, const double c) {
        double discriminant = b * b - 4 * a * c;
        if (discriminant > 0) {
            double sol1 = (-b - sqrt(discriminant)) / (2 * a);
            double sol2 = (-b + sqrt(discriminant)) / (2 * a);
            return std::tuple<unsigned int, double, double>(2, sol1, sol2);
        }
        else if (discriminant == 0) {
            double sol = -b / (2 * a);
            return std::tuple<unsigned int, double, double>(1, sol, 0);
        }
        return std::tuple<unsigned int, double, double>(0, 0, 0);
    }

    double riemannSum(double (*func)(double), const double a, const double b, const int samples) {
        double step = (b - a) / samples;
        double est = 0.0;
        for (double c = a; c < b; c+=step) {
            est += step * (*func)(c);
        }
        return est;
    }

    double sinAzimuth(const vec3<double> w) {
        double s = sinZenith(w);
        return std::abs(s) < std::numeric_limits<double>::epsilon() ? 0 : math::clamp<double>(w.getY() / s, -1.0, 1.0);
    }

    double sin2Azimuth(const vec3<double> w) {
        double s = sinAzimuth(w);
        return s * s;
    }

    double cosAzimuth(const vec3<double> w) {
        double s = sinZenith(w);
        return std::abs(s) < std::numeric_limits<double>::epsilon() ? 1 : math::clamp<double>(w.getX() / s, -1.0, 1.0);
    }

    double cos2Azimuth(const vec3<double> w) {
        double c = cosAzimuth(w);
        return c * c;
    }

    double tanAzimuth(const vec3<double> w) {
        return sinAzimuth(w) / cosAzimuth(w);
    }

    double tan2Azimuth(const vec3<double> w) {
        return sin2Azimuth(w) / cos2Azimuth(w);
    }

    double sinZenith(const vec3<double> w) {
        return std::sqrt(sin2Zenith(w));
    }

    double sin2Zenith(const vec3<double> w) {
        return std::max(0.0, 1.0 - cos2Zenith(w));
    }

    double cosZenith(const vec3<double> w) {
        return w.getZ();
    }

    double cos2Zenith(const vec3<double> w) {
        return w.getZ() * w.getZ();
    }

    double tanZenith(const vec3<double> w) {
        return sinZenith(w) / cosZenith(w);
    }

    double tan2Zenith(const vec3<double> w) {
        return sin2Zenith(w) / cos2Zenith(w);
    }
}
