//
//  screen.hpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 23/3/2022.
//

#ifndef screen_hpp
#define screen_hpp

#include <vector>

#include "math.hpp"

#include "camera.hpp"
#include "primatives.hpp"

#include "ray.hpp"
#include "rayhit.hpp"

using namespace math;
using namespace primatives;

namespace renderer {

    class screen {
    public:
        screen(camera* mainCamera, unsigned int width, unsigned int height, color refreshColor = color(0.0, 0.0, 0.0));

        ray screenToRay(unsigned int x, unsigned int y, double dx = 0, double dy = 0);
        int render(const std::vector<primative*>* world, const unsigned int aaSamples);
    private:
        camera* mainCamera;
        unsigned int width;
        unsigned int height;
        color refreshColor;
        
        bool castRay(const std::vector<primative*>* world, const ray ray, rayhit* hit);
        bool castBouncingRay(const std::vector<primative*>* world, const ray ray, color* outColor, unsigned int depth = 0);
        std::vector<vec2<double>> calculateSamplePositions(const unsigned int samples);
        color calculatePixel(const std::vector<primative*>* world, unsigned int x, unsigned int y, unsigned int samples, std::vector<vec2<double>> samplePositions);
    };
}

#endif /* screen_hpp */
