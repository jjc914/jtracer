//
//  screen.cpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 23/3/2022.
//

#include <fstream>

#include "screen.hpp"

namespace renderer {

    screen::screen(camera* mainCamera, unsigned int width, unsigned int height, color refreshColor) :
                mainCamera(mainCamera), width(width), height(height), refreshColor(refreshColor) {
    }

    ray screen::screenToRay(const unsigned int x, const unsigned int y, const double dx, const double dy) {
        double viewportWidth = mainCamera->getViewportWidth();
        double viewportHeight = mainCamera->getViewportHeight();
        double focalLength = mainCamera->getFocalLength();
        
        double xF = ((double)x + dx) / (width - 1);
        double yF = ((double)y + dy) / (height - 1);
        double xR = viewportWidth * xF - (viewportWidth / 2);
        double yR = viewportHeight * yF - (viewportHeight / 2);
        
        return ray(mainCamera->getPosition(), vec3<double>(xR, yR, -focalLength));
    }

    int screen::render(const std::vector<primative*>* world, const unsigned int samples, const unsigned int bounces, const unsigned int reflections, const std::string fileName) {
        debug::bar progressBar = debug::bar();
        
        std::vector<vec2<double>> samplePositions = this->calculateSamplePositions(samples);
        
        std::ofstream file(fileName);
        file << "P3" << "\n";
        file << width << " " << height << "\n";
        file << 255 << "\n";
        int i = 1;
        for (int y = height - 1; y >= 0; y--) {
            for (int x = 0; x < width; x++) {
                color c = this->calculatePixel(world, x, y, samples, samplePositions, bounces, reflections);
                c.clamp();
                c.gammaCorrect();
                file << (int)(c.getR() * 255.0) << " " << (int)(c.getG() * 255.0) << " " << (int)(c.getB() * 255.0) << "   ";
                progressBar.setProgress((double)i / (width * height));
                progressBar.print();
                i++;
            }
            file << "\n";
        }
        file.close();
        
        std::ifstream f(std::to_string(width) + "p" + std::to_string(samples) + "s.ppm");
        return f.good();
    }

    bool screen::castRay(const std::vector<primative*>* world, const ray r, rayhit* hit) {
        primative* closestPrim = nullptr;
        double closestDist = INFINITY;
        vec3<double> closestPos;
        
        for (primative* prim : *world) {
            std::list<vec3<double>> intersects = prim->intersect(r);
            if (intersects.size() > 0) {
                vec3<double> intersect = intersects.front();
                double dist = vec3<double>::distance(intersect, r.getOrigin());
                if (dist < closestDist) {
                    closestPrim = prim;
                    closestDist = dist;
                    closestPos = intersect;
                }
            }
        }
        
        if (closestPrim) {
            hit->name = closestPrim->getName();
            hit->position = closestPos;
            hit->prim = closestPrim;
            hit->normal = closestPrim->normalAtPoint(r.getOrigin(), closestPos);
            return true;
        }
        
        return false;
    }

    color screen::tracePath(const std::vector<primative*>* world, const ray r, const int bounces, const int reflections, const int depth) {
        if (depth > bounces) {
            return color(0.0, 0.0, 0.0);
        }
        
        rayhit hit = rayhit();
        if (castRay(world, r, &hit)) {
            color average = color(0.0, 0.0, 0.0);
            for (int i = 0; i < reflections; i++) {
                // vec3<double> reflectionDirection = hit.prim->getMaterial()->sampleBounceDirection(r.getDirection(), hit.normal);
                vec3<double> reflectionDirection = rejectionSampleHemisphere(hit.normal);
                ray reflectionRay = ray(hit.position + reflectionDirection * 0.001, reflectionDirection);
                if (fabs(hit.prim->getMaterial()->getEmissionPower()) < std::numeric_limits<double>::epsilon()) {
                    average += (hit.prim->getMaterial()->getEmissionColor() * hit.prim->getMaterial()->getEmissionPower() + 
                               tracePath(world, reflectionRay, bounces, reflections, depth + 1) * vec3<double>::dot(hit.normal, reflectionDirection) * hit.prim->getMaterial()->evaluate(reflectionDirection, r.getDirection()) * 2.0);
                } else {
                    average += hit.prim->getMaterial()->getEmissionColor() * hit.prim->getMaterial()->getEmissionPower();
                }
            }
            average /= reflections;
            return average;
        }
        if (depth <= 0) return refreshColor;
        
        return color(0.0, 0.0, 0.0);
    }

    color screen::calculatePixel(const std::vector<primative*>* world, const int x, const int y, const int samples, const std::vector<vec2<double>> samplePositions, const int bounces, const int reflections) {
        color pixelColor = color(0.0, 0.0, 0.0);
        
        for (vec2<double> samplePos : samplePositions) {
            ray r = this->screenToRay(x, y, samplePos.getX(), samplePos.getY());
            color sampleColor = this->tracePath(world, r, bounces, reflections);
            pixelColor += sampleColor;
        }
//        pixelColor /= 10.0;
        return pixelColor / samples;
    }

    std::vector<vec2<double>> screen::calculateSamplePositions(const unsigned int samples) {
        // TODO: adaptive sampling
        std::vector<vec2<double>> samplePositions;
        
        int samplesSqrtRound = round(sqrt(samples));
        int remainder = samples - samplesSqrtRound * samplesSqrtRound;
        
        for (int sy = 0; sy < samplesSqrtRound; sy++) {
            int samplesSqrtNew = samplesSqrtRound + roundAwayFromZero((double)remainder / (double)samplesSqrtRound);
            remainder -= roundAwayFromZero((double)remainder / (double)samplesSqrtRound);
            for (int sx = 0; sx < samplesSqrtNew; sx++) {
                double dx;
                double dy;
                if (samplesSqrtNew == 1) {
                    dx = 0;
                } else {
                    dx = ((double)sx / ((double)samplesSqrtNew - 1.0)) - 0.5;
                }
                if (samplesSqrtRound == 1) {
                    dy = 0;
                } else {
                    dy = ((double)sy / ((double)samplesSqrtNew - 1.0)) - 0.5;
                }
                samplePositions.push_back(vec2<double>(dx, dy));
            }
        }
        return samplePositions;
    }
}
