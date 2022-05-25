//
//  sphere.hpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 24/3/2022.
//

#ifndef sphere_hpp
#define sphere_hpp

#include <list>

#include "vec3.hpp"
#include "primative.hpp"
#include "color.hpp"

using namespace math;

namespace primatives {

    class sphere : public primative {
    public:
        sphere(std::string name, vec3<double> position, double radius, color pColor);
        
        std::list<vec3<double>> intersect(const ray ray) const override;
    private:
        double radius;
        color pColor;
    };
}

#endif /* sphere_hpp */
