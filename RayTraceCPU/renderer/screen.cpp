//
//  screen.cpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 23/3/2022.
//

#include <fstream>
#include <iostream>

#include "screen.hpp"

namespace renderer {

    screen::screen(camera* mainCamera, unsigned int width, unsigned int height, color refreshColor) :
                mainCamera(mainCamera), width(width), height(height), refreshColor(refreshColor) {
    }

    ray screen::screenToRay(unsigned int x, unsigned int y, double dx, double dy) {
        double viewportWidth = mainCamera->getViewportWidth();
        double viewportHeight = mainCamera->getViewportHeight();
        double focalLength = mainCamera->getFocalLength();
        
        double xF = ((double)x + dx) / (width - 1);
        double yF = ((double)y + dy) / (height - 1);
        double xR = viewportWidth * xF - (viewportWidth / 2);
        double yR = viewportHeight * yF - (viewportHeight / 2);
        
        return ray(mainCamera->getPosition(), vec3<double>(xR, yR, -focalLength));
    }

    int screen::render(const std::vector<primative*>* world, const unsigned int aaSamples) {
        std::vector<vec2<double>> aaSamplePositions = this->calculateSamplePositions(aaSamples);
        
        std::ofstream file("output.ppm");
        file << "P3" << "\n";
        file << width << " " << height << "\n";
        file << 255 << "\n";
        for (int y = height - 1; y >= 0; y--) {
            for (int x = 0; x < width; x++) {
                color c = this->calculatePixel(world, x, y, aaSamples, aaSamplePositions);
                file << (int)(c.getR() * 255.0) << " " << (int)(c.getG() * 255.0) << " " << (int)(c.getB() * 255.0) << "   ";
            }
            file << "\n";
        }
        file.close();
        
        std::ifstream f("output.ppm");
        return f.good();
    }

    bool screen::castRay(const std::vector<primative*>* world, const ray r, rayhit* hit) {
        double closestDst = INFINITY;
        std::string closestName;
        vec3<double> closestOrigin;
        vec3<double> closestNormal;
        color closestColor = refreshColor;
        
        bool didHit = false;
        for (primative* p : *world) {
            std::list<vec3<double>> points = p->intersect(r);
            if (points.size() > 0) {
                vec3<double> cls = points.front();
                vec3<double> vDn = (cls - p->getPosition()).normalize();
                double dst = cls.getMagnitude();
                if (dst < closestDst) {
                    closestName = p->getName();
                    closestColor = p->getColor();
                    closestDst = dst;
                    closestOrigin = cls;
                    closestNormal = vDn;
                    didHit = true;
                }
            }
        }
        if (hit) {
            hit->name = closestName;
            hit->position = closestOrigin;
            hit->normal = closestNormal;
            hit->pColor = closestColor;
        }
        return didHit;
    }

    bool screen::castBouncingRay(const std::vector<primative*>* world, const ray r, color* outColor, unsigned int depth) {
        if (depth > 10) {
            return false;
        }
        rayhit hit;
        if (this->castRay(world, r, &hit)) {
            (*outColor).setR(outColor->getR() * hit.pColor.getR());
            (*outColor).setG(outColor->getG() * hit.pColor.getG());
            (*outColor).setB(outColor->getB() * hit.pColor.getB());
            // TODO: Use BSDF
//            vec3<double> bounce = vec3<double>::reflect(r.getDirection(), hit.normal);
            vec3<double> bounce = rejectionSampleHemisphere(hit.normal);
            bounce.normalize();
            
            *outColor *=  1.0 - (depth / 10.0);
            ray rBounce(hit.position, bounce);
            this->castBouncingRay(world, rBounce, outColor, depth + 1);
            return true;
        }
        (*outColor).setR(outColor->getR() * refreshColor.getR());
        (*outColor).setG(outColor->getG() * refreshColor.getG());
        (*outColor).setB(outColor->getB() * refreshColor.getB());
        return false;
    }

    color screen::calculatePixel(const std::vector<primative*>* world, unsigned int x, unsigned int y, unsigned int samples, std::vector<vec2<double>> samplePositions) {
        color c = color(0.0, 0.0, 0.0);
        
        for (vec2<double> samplePos : samplePositions) {
            ray r = this->screenToRay(x, y, samplePos.getX(), samplePos.getY());
            color sampleColor(1.0, 1.0, 1.0);
            this->castBouncingRay(world, r, &sampleColor);
            c += sampleColor / samples;
        }
        return c;
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
