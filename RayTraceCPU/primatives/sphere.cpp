//
//  sphere.cpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 24/3/2022.
//

#include "sphere.hpp"
#include <iostream>

namespace primatives {

    sphere::sphere(std::string name, vec3<double> position, double radius, color pColor) : primative(name, position, pColor), radius(radius) {
    }

    std::list<vec3<double>> sphere::intersect(const ray ray) const {
        std::list<vec3<double>> points;
        
        vec3<double> pOs = position;
        vec3<double> pOr = ray.getOrigin();
        vec3<double> vDr = ray.getDirection();
        vec3<double> vLo = pOs - pOr;
        
        double m = vec3<double>::dot(vLo, vDr);
        if (m > 0) {
            vec3<double> vLr = pOr + vDr * m;
            // TODO: do the maths for when the ray origin is inside the sphere
            double l = vec3<double>::distance(vLr, pOs);
            if (l < radius) {
                double dI = sqrt(radius * radius - l * l);
                vec3<double> vLdi = vDr * dI;
                vec3<double> pIa = vLr - vLdi;
                vec3<double> pIb = vLr + vLdi;
                
                points.push_back(pIa);
                points.push_back(pIb);
            }
        }
        return points;
    }
}
