//
//  math.cpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 23/3/2022.
//

#include "math.hpp"

namespace math {

    double rad2deg(double rad) {
        return rad * (180 / M_PI);
    }

    double deg2rad(double deg) {
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

    vec3<double> rejectionSampleHemisphere(vec3<double> normal) {
        vec3<double> vec = rejectionSampleSphere();
        if (vec3<double>::dot(vec, normal) < 0) {
            vec *= -1.0;
        }
        return vec;
    }

    std::tuple<unsigned int, double, double> solveQuadratic(double a, double b, double c) {
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
}
