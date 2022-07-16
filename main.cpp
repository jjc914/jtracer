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
#include "materials.hpp"

using namespace materials;
using namespace primatives;
using namespace renderer;

int runRender() {
    camera cam(vec3<double>(0.0, 1.0, 0.0), 16.0 / 9.0, 70);
//    screen scrn(&cam, 240, 135, color(0.0, 0.0, 0.0));
    screen scrn(&cam, 480, 270, color(0.0, 0.0, 0.0));
//    screen scrn(&cam, 1920, 1080, color(0.8, 0.9, 1.0));
    
    std::vector<primative*> world1;
    {
        lambertian* red = new lambertian(color(1.0, 0.0, 0.0));
        lambertian* green = new lambertian(color(0.0, 1.0, 0.0));
        lambertian* blue = new lambertian(color(0.0, 0.0, 1.0));
        lambertian* flr = new lambertian(color(0.8, 0.8, 0.8));
        lambertian* sky = new lambertian(color(0.0, 0.0, 0.0), color(1.0, 1.0, 1.0), 1.0);

        sphere* s1 = new sphere("red", red, vec3<double>(0.0, 2.95, -13.0), 2.0);
        sphere* s2 = new sphere("green", green, vec3<double>(-2.0, -0.5, -13.0), 2.0);
        sphere* s3 = new sphere("blue", blue, vec3<double>(2.0, -0.5, -13.0), 2.0);
        sphere* floor = new sphere("floor", flr, vec3<double>(0.0, -1002.5, -13.0), 1000.0);
        sphere* skybox = new sphere("skybox", sky, vec3<double>(0.0, 0.0, 0.0), 1000.0);

        world1.push_back(s1);
        world1.push_back(s2);
        world1.push_back(s3);
        world1.push_back(floor);
        world1.push_back(skybox);
    }
    
    std::vector<primative*> world2;
    {
        lambertian* red = new lambertian(color(1.0, 0.0, 0.0));
        lambertian* green = new lambertian(color(0.0, 1.0, 0.0));
        lambertian* blue = new lambertian(color(0.0, 0.0, 1.0));
        lambertian* flr = new lambertian(color(0.8, 0.8, 0.8));
        lambertian* redEmissive = new lambertian(color(0.0, 0.0, 0.0), color(1.0, 0.2, 0.2), 10.0);
        lambertian* blueEmissive = new lambertian(color(0.0, 0.0, 0.0), color(0.2, 0.2, 1.0), 15.0);
        
        sphere* s1 = new sphere("red", red, vec3<double>(0.0, 2.95, -13.0), 2.0);
        sphere* s2 = new sphere("green", green, vec3<double>(-2.0, -0.5, -13.0), 2.0);
        sphere* s3 = new sphere("blue", blue, vec3<double>(2.0, -0.5, -13.0), 2.0);
        sphere* floor = new sphere("floor", flr, vec3<double>(0.0, -1002.5, -13.0), 1000.0);
        sphere* redLight = new sphere("redLight", redEmissive, vec3<double>(-4.0, 0.5, -14.5), 2.0);
        sphere* blueLight = new sphere("blueLight", blueEmissive, vec3<double>(4.0, 4.0, -12.0), 2.0);
        
        world2.push_back(s1);
        world2.push_back(s2);
        world2.push_back(s3);
        world2.push_back(floor);
        world2.push_back(redLight);
        world2.push_back(blueLight);
    }
    
    std::vector<primative*> world3;
    {
        lambertian* blue = new lambertian(color(0.6, 0.6, 1.0));
        lambertian* emissive = new lambertian(color(0.0, 0.0, 0.0), color(1.0, 1.0, 1.0), 50.0);
        
        sphere* container = new sphere("container", blue, vec3<double>(0.0, 0.0, 0.0), 10.0);
        sphere* light = new sphere("light", emissive, vec3<double>(0.0, 2.0, -8.0), 1.0);
        
        world3.push_back(container);
        world3.push_back(light);
    }
    
    std::vector<primative*> world4;
    {
        lambertian* greyDiffuse = new lambertian(color(0.7, 0.7, 0.7));
        lambertian* greenDiffuse = new lambertian(color(0.4, 0.7, 0.2));
        lambertian* redDiffuse = new lambertian(color(0.7, 0.15, 0.1));
        lambertian* lightMat = new lambertian(color(0.0, 0.0, 0.0), color(1.0, 1.0, 0.7), 10.0);
        lambertian* ambient = new lambertian(color(0.0, 0.0, 0.0), color(1.0, 1.0, 1.0), 0.02);
        lambertian* boxMat = new lambertian(color(0.7, 0.7, 0.7));
        lambertian* sphereMat = new lambertian(color(0.7, 0.7, 0.7));

        box* floor = new box("floor", greyDiffuse, vec3<double>(-2.0, -1.0, -6.0), vec3<double>(2.0, -0.1, -3.0));
        box* rightWall = new box("rightWall", greenDiffuse, vec3<double>(2.0, -1.0, -6.0), vec3<double>(3.0, 3.0, -3.0));
        box* leftWall = new box("leftWall", redDiffuse, vec3<double>(-3.0, -1.0, -6.0), vec3<double>(-2.0, 3.0, -3.0));
        box* ceiling = new box("ceiling", greyDiffuse, vec3<double>(-2.0, 3.0, -6.0), vec3<double>(2.0, 4.0, -3.0));
        box* backWall = new box("backWall", greyDiffuse, vec3<double>(-3.0, -1.0, -7.0), vec3<double>(3.0, 3.0, -6.0));
        box* light = new box("light", lightMat, vec3<double>(-0.75, 2.95, -6.0), vec3<double>(0.75, 3.0, -5.0));
        sphere* skybox = new sphere("skybox", ambient, vec3<double>(), 1000.0);
        
        box* b1 = new box("b1", boxMat, vec3<double>(-0.75, 0.9, -5.0), 1.0, 2.0, 1.0);
        sphere* s1 = new sphere("s1", sphereMat, vec3<double>(0.75, 0.4, -3.5), 0.5);

        world4.push_back(floor);
        world4.push_back(rightWall);
        world4.push_back(leftWall);
        world4.push_back(ceiling);
        world4.push_back(backWall);
        world4.push_back(light);
        world4.push_back(skybox);
        
        world4.push_back(b1);
        world4.push_back(s1);
    }
    
    // TODO: Importance sampling
    
//    return scrn.render(&world2, 4, 2, 5);
//    return scrn.render(&world4, 16, 2, 1);
    return scrn.render(&world4, 16, 3, 32);
//    return scrn.render(&world3, 128, 2, 5);
//    return scrn.render(&world3, 2048, 2, 1);
//    return scrn.render(&world2, 8192, 2, 3);
}

int main(int argc, const char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    
    int returnCode = runRender();
        
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << "Program finished in " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms" << std::endl;
    
    return returnCode;
}
