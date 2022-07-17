//
//  sphere.hpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 24/3/2022.
//

#ifndef sphere_hpp
#define sphere_hpp

#include <list>

#include "primative.hpp"
#include "math/vec3.hpp"
#include "materials/brdf.hpp"

using namespace math;
using namespace materials;

namespace primatives {

    class sphere : public primative {
    public:
        sphere(const std::string name, brdf* mat, const vec3<double> position, const double radius);
        
        std::list<vec3<double>> intersect(const ray r) const override;
        vec3<double> normalAtPoint(const vec3<double> origin, const vec3<double> point) const override;
        
        bool intersects(const ray r) const override;
        bool encloses(const vec3<double> point) const override;
    private:
        double radius;
    };
}

#endif /* sphere_hpp */
