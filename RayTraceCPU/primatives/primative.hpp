//
//  primative.hpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 24/3/2022.
//

#ifndef primative_hpp
#define primative_hpp

#include <list>

#include "vec3.hpp"
#include "ray.hpp"
#include "brdf.hpp"

using namespace math;
using namespace materials;

namespace primatives {

    class primative {
    public:
        virtual std::list<vec3<double>> intersect(const ray r) const = 0;
        virtual vec3<double> normalAtPoint(const vec3<double> origin, vec3<double> point) const = 0;
        
        virtual bool intersects(const ray r) const = 0;
        virtual bool encloses(const vec3<double> point) const = 0;
        
        std::string getName() const;
        brdf* getMaterial() const;
        vec3<double> getPosition() const;
    protected:
        primative(std::string name, brdf* mat, vec3<double> position);
        
        std::string name;
        brdf* mat;
        vec3<double> position;
    };
}

#endif /* primative_hpp */
