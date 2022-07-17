//
//  screen.hpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 23/3/2022.
//

#ifndef screen_hpp
#define screen_hpp

#include <vector>

#include "math/math.hpp"
#include "debug/bar.hpp"

#include "camera.hpp"
#include "primatives/primatives.hpp"

#include "math/ray.hpp"
#include "math/rayhit.hpp"

using namespace math;
using namespace primatives;

namespace renderer {

    class screen {
    public:
        screen(camera* mainCamera, unsigned int width, unsigned int height, color refreshColor = color(0.0, 0.0, 0.0));

        ray screenToRay(const unsigned int x, const unsigned int y, const double dx = 0, const double dy = 0);
        int render(const std::vector<primative*>* world, const unsigned int aaSamples, const unsigned int bounces, const unsigned int reflections);
    private:
        camera* mainCamera;
        unsigned int width;
        unsigned int height;
        color refreshColor;
        
        bool castRay(const std::vector<primative*>* world, const ray ray, rayhit* hit);
        color tracePath(const std::vector<primative*>* world, const ray ray, const int bounces, const int reflections, const int depth = 0);
    
        std::vector<vec2<double>> calculateSamplePositions(const unsigned int samples);
        color calculatePixel(const std::vector<primative*>* world, const int x, const int y, const int samples, const std::vector<vec2<double>> samplePositions, const int bounces, const int reflections);
    };
}

#endif /* screen_hpp */
