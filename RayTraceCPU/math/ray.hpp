//
//  ray.hpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 22/3/2022.
//

#ifndef ray_hpp
#define ray_hpp

#include "vec3.hpp"
#include "color.hpp"

namespace math {

    class ray {
    public:
        ray(vec3<double> origin, vec3<double> direction);
        
        vec3<double> getOrigin() const;
        vec3<double> getDirection() const;
    private:
        vec3<double> origin;
        vec3<double> direction;
    };
}

#endif /* ray_hpp */
