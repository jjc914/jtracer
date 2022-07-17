//
//  camera.cpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 22/3/2022.
//

#include "camera.hpp"

namespace renderer {

    camera::camera(vec3<double> position, const double aspectRatio, const double angleOfView) :
    position(position), aspectRatio(aspectRatio), angleOfView(angleOfView) {
        double verticalAngleOfView = 2 * rad2deg(atan(tan(deg2rad(angleOfView / 2)) / aspectRatio));
        viewportHeight = 2 * focalLength * tan(deg2rad(verticalAngleOfView / 2));
        viewportWidth = 2 * focalLength * tan(deg2rad(angleOfView / 2));
    }

    vec3<double> camera::getPosition() const {
        return position;
    }

    double camera::getFocalLength() const {
        return focalLength;
    }

    double camera::getViewportWidth() const {
        return viewportWidth;
    }

    double camera::getViewportHeight() const {
        return viewportHeight;
    }
}
