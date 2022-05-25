//
//  math.h
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 22/3/2022.
//

#ifndef math_hpp
#define math_hpp

#include <math.h>
#include <tuple>

#include "vec2.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "rayhit.hpp"

#include "color.hpp"

namespace math {

    double rad2deg(double rad);
    double deg2rad(double deg);
    vec3<double> rejectionSampleSphere();
    vec3<double> rejectionSampleHemisphere(vec3<double> normal);
    std::tuple<unsigned int, double, double> solveQuadratic(double a, double b, double c);

    template<typename T>
    T randRange(T min, T max) {
        return (T)(min + (rand() / (double)RAND_MAX) * (max - min));
    }

    template<typename T>
    int roundAwayFromZero(T val) {
        if (val > 0) {
            return ceil(val);
        } else {
            return floor(val);
        }
    }
}

#endif /* math_hpp */
