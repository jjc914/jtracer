#include <iostream>
#include <vector>
#include <chrono>

#include "math/mat3x3.hpp"
#include "renderer/renderer.hpp"
#include "primatives/primatives.hpp"
#include "materials/materials.hpp"

using namespace materials;
using namespace primatives;
using namespace renderer;
using namespace math;

// right, up, out of screen: positive
int runRender() {
    camera cam(vec3<double>(0.0, 1.0, 0.0), 16.0 / 9.0, 70);
//    screen scrn(&cam, 240, 135, color(0.0, 0.0, 0.0));
    // screen scrn(&cam, 480, 270, color(0.0, 0.0, 0.0));
    screen scrn(&cam, 256, 144, color(0.0, 0.0, 0.0));
//    screen scrn(&cam, 1920, 1080, color(0.8, 0.9, 1.0));
    
    std::vector<primative*> world1;
    {
        lambertian* red = new lambertian(color(1.0, 0.0, 0.0));
        lambertian* green = new lambertian(color(0.0, 1.0, 0.0));
        // beckmannspizzichino* greenDist = new beckmannspizzichino(0.3, 0.3);
        // torrancesparrow* green = new torrancesparrow(color(1.0, 1.0, 1.0), green);
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
        // beckspizz* boxMat = new beckspizz(color(0.7, 0.7, 0.7), 10.0, 10.0);
        lambertian* sphereMat = new lambertian(color(0.7, 0.7, 0.7));
        // beckspizz* sphereMat = new beckspizz(color(0.7, 0.7, 0.7), 10.0, 10.0);

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

    std::vector<primative*> world5;
    {
        lambertian* one = new lambertian(color(0.40, 0.26, 0.78));
        lambertian* two = new lambertian(color(0.30, 0.45, 0.21));
        lambertian* thr = new lambertian(color(0.09, 0.58, 0.62));
        lambertian* fou = new lambertian(color(0.15, 0.33, 0.37));
        lambertian* fiv = new lambertian(color(0.01, 0.41, 0.32));
        lambertian* six = new lambertian(color(0.70, 0.89, 0.27));
        lambertian* sev = new lambertian(color(0.67, 0.73, 0.96));
        lambertian* eig = new lambertian(color(0.44, 0.08, 0.79));
        lambertian* nin = new lambertian(color(0.22, 0.51, 0.89));
        lambertian* ten = new lambertian(color(0.26, 0.19, 0.66));
        
        lambertian* sky = new lambertian(color(0.0, 0.0, 0.0), color(1.0, 1.0, 1.0), 1.0);

        sphere* s1 = new sphere("s1", one, vec3<double>(1.77 * 2.0, -2.37 + 0.5, 0.67 - 10.0), 1.0);
        sphere* s2 = new sphere("s2", two, vec3<double>(1.91 * 2.0, 2.87 + 0.5, -0.93 - 10.0), 1.0);
        sphere* s3 = new sphere("s3", thr, vec3<double>(2.30 * 2.0, -0.81 + 0.5, -0.10 - 10.0), 1.0);
        sphere* s4 = new sphere("s4", fou, vec3<double>(-0.19 * 2.0, 0.63 + 0.5, 2.81 - 10.0), 1.0);
        sphere* s5 = new sphere("s5", fiv, vec3<double>(-1.84 * 2.0, -2.10 + 0.5, 0.99 - 10.0), 1.0);
        sphere* s6 = new sphere("s6", six, vec3<double>(1.59 * 2.0, 1.75 + 0.5, 2.99 - 10.0), 1.0);
        sphere* s7 = new sphere("s7", sev, vec3<double>(-2.12 * 2.0, 2.61 + 0.5, -0.66 - 10.0), 1.0);
        sphere* s8 = new sphere("s8", eig, vec3<double>(-2.36 * 2.0, -2.03 + 0.5, -0.69 - 10.0), 1.0);
        sphere* s9 = new sphere("s9", nin, vec3<double>(0.00 * 2.0, 0.05 + 0.5, -0.56 - 10.0), 1.0);
        sphere* s10 = new sphere("s10", ten, vec3<double>(-1.22 * 2.0, 0.81 + 0.5, 1.56 - 10.0), 1.0);
        
        sphere* skybox = new sphere("skybox", sky, vec3<double>(0.0, 0.0, 0.0), 1000.0);

        world5.push_back(s1);
        world5.push_back(s2);
        world5.push_back(s3);
        world5.push_back(s4);
        world5.push_back(s5);
        world5.push_back(s6);
        world5.push_back(s7);
        world5.push_back(s8);
        world5.push_back(s9);
        world5.push_back(s10);
        world5.push_back(skybox);
    }
    
    // TODO: Importance sampling
    scrn.render(&world1, 16, 3, 64, "world1gt-16spp.ppm");
    scrn.render(&world1, 8, 3, 32, "world1-8spp.ppm");
    scrn.render(&world1, 4, 3, 8, "world1-4spp.ppm");

    scrn.render(&world2, 16, 3, 64, "world2-16spp.ppm");
    scrn.render(&world2, 8, 3, 32, "world2-8spp.ppm");
    scrn.render(&world2, 4, 3, 8, "world2-4spp.ppm");

    scrn.render(&world3, 16, 3, 64, "world3-16spp.ppm");
    scrn.render(&world3, 8, 3, 32, "world3-8spp.ppm");
    scrn.render(&world3, 4, 3, 8, "world3-4spp.ppm");

    scrn.render(&world4, 16, 3, 64, "world4-16spp.ppm");
    scrn.render(&world4, 8, 3, 32, "world4-8spp.ppm");
    scrn.render(&world4, 4, 3, 8, "world4-4spp.ppm");

    scrn.render(&world5, 16, 3, 64, "world5-16spp.ppm");
    scrn.render(&world5, 8, 3, 32, "world5-8spp.ppm");
    scrn.render(&world5, 4, 3, 8, "world5-4spp.ppm");

    // scrn.render(&world1, 16, 2, 4, "1.ppm");
    // scrn.render(&world2, 16, 2, 4, "2.ppm");
    // scrn.render(&world4, 16, 2, 4, "4.ppm");
    // scrn.render(&world5, 16, 2, 4, "5.ppm");
   return 1;
//    return scrn.render(&world2, 9, 3, 16);
//    return scrn.render(&world2, 4, 3, 8);
//    return scrn.render(&world1, 16, 3, 2);
    // return scrn.render(&world4, 16, 3, 32);
    // return scrn.render(&world4, 16, 3, 8);
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
