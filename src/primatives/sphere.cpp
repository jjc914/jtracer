//
//  sphere.cpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 24/3/2022.
//

#include "sphere.hpp"

namespace primatives {

    sphere::sphere(const std::string name, brdf* mat, const vec3<double> position, const double radius) : primative(name, mat, position), radius(radius) {
    }

    std::list<vec3<double>> sphere::intersect(const ray r) const {
        std::list<vec3<double>> points;
        
        vec3<double> pOs = position;
        vec3<double> pOr = r.getOrigin();
        vec3<double> vDr = r.getDirection();
        vec3<double> vLo = pOs - pOr;
        
        double m = vec3<double>::dot(vLo, vDr);
        vec3<double> vLr = pOr + vDr * m;
        double l = vec3<double>::distance(vLr, pOs);
        double oL = vec3<double>::distance(pOs, pOr);
        
        if ((m > 0 && oL >= radius) || oL <= radius) {
            if (l <= radius) {
                double dI = sqrt(radius * radius - l * l);
                vec3<double> vLdi = vDr * dI;
                vec3<double> pIa = vLr - vLdi;
                vec3<double> pIb = vLr + vLdi;
                
                if (oL >= radius)
                    points.push_back(pIa);
                points.push_back(pIb);
            }
        }
        return points;
    }

    vec3<double> sphere::normalAtPoint(const vec3<double> origin, const vec3<double> point) const {
        vec3<double> normal = (point - position).normalize();
        if (encloses(origin)) normal *= -1;
        return normal;
    }

    bool sphere::intersects(const ray r) const {
        vec3<double> pOs = position;
        vec3<double> pOr = r.getOrigin();
        vec3<double> vDr = r.getDirection();
        vec3<double> vLo = pOs - pOr;
        
        double m = vec3<double>::dot(vLo, vDr);
        double oL = vec3<double>::distance(pOs, pOr);
        
        return (m > 0 && oL >= radius) || oL <= radius;
    }

    bool sphere::encloses(const vec3<double> point) const {
        return vec3<double>::distance(position, point) < radius;
    }
}
