//
//  camera.hpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 22/3/2022.
//

#ifndef camera_hpp
#define camera_hpp

#include "math.hpp"

using namespace math;

namespace renderer {

    class camera {
    public:
        camera(vec3<double> position, const double aspectRatio, const double angleOfView);
        
        vec3<double> getPosition() const;
        double getFocalLength() const;
        double getViewportWidth() const;
        double getViewportHeight() const;
    private:
        const double focalLength = 1.0;
        
        vec3<double> position;
        double aspectRatio;
        double angleOfView;
        double viewportWidth, viewportHeight;
    };
}

#endif /* camera_hpp */
