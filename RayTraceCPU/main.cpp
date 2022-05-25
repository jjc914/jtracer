//
//  main.cpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 22/3/2022.
//

#include <iostream>
#include <vector>
#include <chrono>

#include "renderer.hpp"
#include "primatives.hpp"

using namespace renderer;
using namespace primatives;

int run() {
    camera cam(vec3<double>(0.0, 1.0, 13.0), 16.0 / 9.0, 70);
    screen scrn(&cam, 720, 405, color(0.8, 0.9, 1.0));
//    screen scrn(&cam, 1920, 1080, color(0.8, 0.9, 1.0));
    
    std::vector<primative*> world;
    sphere s1("green", vec3<double>(-2.0, -0.5, 0.0), 2.0, color(0.4, 1.0, 0.3));
    sphere s2("blue", vec3<double>(2.0, -0.5, 0.0), 2.0, color(0.4, 0.3, 1.0));
    sphere s3("red", vec3<double>(0.0, 2.95, 0.0), 2.0, color(1.0, 0.4, 0.3));
//    sphere skybox("skybox", vec3<double>(0.0, 0.0, 0.0), 100.0, color (1.0, 0.0, 0.0));
    sphere floor("floor", vec3<double>(0.0, -1002.5, 0.0), 1000.0, color(0.8, 0.8, 0.8));
    world.push_back(&s1);
    world.push_back(&s2);
    world.push_back(&s3);
    world.push_back(&floor);
//    world.push_back(&skybox);
    
    // TODO: Importance sampling
    
    return scrn.render(&world, 16);
//    return scrn.render(&world, 128);
}

int main(int argc, const char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    
    int returnCode = run();
        
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << "Program finished in " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms" << std::endl;
    
    return returnCode;
}
