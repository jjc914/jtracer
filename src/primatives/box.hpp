//
//  box.hpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 15/7/2022.
//

#ifndef box_hpp
#define box_hpp

#include <list>

#include "math/vec3.hpp"
#include "primative.hpp"
#include "materials/brdf.hpp"

using namespace math;
using namespace materials;

namespace primatives {

    class box : public primative {
    public:
        box(const std::string name, brdf* mat, const vec3<double> position, const double width, const double height, const double length);
        box(const std::string name, brdf* mat, const vec3<double> corner0, vec3<double> corner1);
        
        std::list<vec3<double>> intersect(const ray r) const override;
        vec3<double> normalAtPoint(const vec3<double> origin, const vec3<double> point) const override;
        
        bool intersects(const ray r) const override;
        bool encloses(const vec3<double> point) const override;
    private:
        vec3<double> corner0;
        vec3<double> corner1;
    };
}

#endif /* box_hpp */
