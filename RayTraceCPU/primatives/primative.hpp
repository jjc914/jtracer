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

using namespace math;

namespace primatives {

    class primative {
    public:
        virtual std::list<vec3<double>> intersect(const ray r) const = 0;
        
        std::string getName() const;
        vec3<double> getPosition() const;
        color getColor() const;
    protected:
        primative(std::string name, vec3<double> position, color pColor);
        
        std::string name;
        vec3<double> position;
        color pColor;
    };
}

#endif /* primative_hpp */
