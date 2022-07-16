//
//  box.cpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 15/7/2022.
//

#include <iostream>
#include "box.hpp"

namespace primatives {

    box::box(const std::string name, brdf* mat, const vec3<double> position, const double width, const double height, const double length) : primative(name, mat, position) {
        double halfWidth = width / 2.0;
        double halfHeight = height / 2.0;
        double halfLength = length / 2.0;
        corner0 = vec3<double>(position.getX() - halfWidth, position.getY() - halfHeight, position.getZ() - halfLength);
        corner1 = vec3<double>(position.getX() + halfWidth, position.getY() + halfHeight, position.getZ() + halfLength);
    }

    box::box(const std::string name, brdf* mat, const vec3<double> corner0, const vec3<double> corner1) : primative(name, mat, vec3<double>()), corner0(corner0), corner1(corner1) {
        position = (corner0 + corner1) / 2.0;
    }

    std::list<vec3<double>> box::intersect(const ray r) const {
        std::list<vec3<double>> points;
        
        vec3<double> pOs = position;
        vec3<double> pOr = r.getOrigin();
        vec3<double> vDr = r.getDirection();
        vec3<double> vLo = pOs - pOr;
        
        if (vec3<double>::dot(vLo, vDr) < 0) return points;
        
        double t0X = (corner0.getX() - r.getOrigin().getX()) / r.getDirection().getX();
        double t1X = (corner1.getX() - r.getOrigin().getX()) / r.getDirection().getX();
        double tMinX, tMaxX;
        if (t0X < t1X) {
            tMinX = t0X;
            tMaxX = t1X;
        } else {
            tMinX = t1X;
            tMaxX = t0X;
        }
        
        double t0Y = (corner0.getY() - r.getOrigin().getY()) / r.getDirection().getY();
        double t1Y = (corner1.getY() - r.getOrigin().getY()) / r.getDirection().getY();
        double tMinY, tMaxY;
        if (t0Y < t1Y) {
            tMinY = t0Y;
            tMaxY = t1Y;
        } else {
            tMinY = t1Y;
            tMaxY = t0Y;
        }
        
        if (tMinX > tMaxY || tMinY > tMaxX) return points;
        
        double t0Z = (corner0.getZ() - r.getOrigin().getZ()) / r.getDirection().getZ();
        double t1Z = (corner1.getZ() - r.getOrigin().getZ()) / r.getDirection().getZ();
        double tMinZ, tMaxZ;
        if (t0Z < t1Z) {
            tMinZ = t0Z;
            tMaxZ = t1Z;
        } else {
            tMinZ = t1Z;
            tMaxZ = t0Z;
        }
        
        if (tMinX > tMaxZ || tMinZ > tMaxX) return points;
        if (tMinY > tMaxZ || tMinZ > tMaxY) return points;

        double tMinInt = std::max(tMinX, std::max(tMinY, tMinZ));
        double tMaxInt = std::min(tMaxX, std::min(tMaxY, tMaxZ));
        points.push_back(r.getOrigin() + r.getDirection() * tMinInt);
        points.push_back(r.getOrigin() + r.getDirection() * tMaxInt);
        
        return points;
    }

    vec3<double> box::normalAtPoint(const vec3<double> origin, const vec3<double> point) const {
        vec3<double> normal;
        if (fabs(point.getX() - corner0.getX()) <= std::numeric_limits<double>::epsilon())
            normal = vec3<double>(-1.0, 0.0, 0.0);
        if (fabs(point.getX() - corner1.getX()) <= std::numeric_limits<double>::epsilon())
            normal = vec3<double>(1.0, 0.0, 0.0);
        if (fabs(point.getY() - corner0.getY()) <= std::numeric_limits<double>::epsilon())
            normal = vec3<double>(0.0, -1.0, 0.0);
        if (fabs(point.getY() - corner1.getY()) <= std::numeric_limits<double>::epsilon())
            normal = vec3<double>(0.0, 1.0, 0.0);
        if (fabs(point.getZ() - corner0.getZ()) <= std::numeric_limits<double>::epsilon())
            normal = vec3<double>(0.0, 0.0, -1.0);
        if (fabs(point.getZ() - corner1.getZ()) <= std::numeric_limits<double>::epsilon())
            normal = vec3<double>(0.0, 0.0, 1.0);
        
        if (encloses(origin)) normal *= -1.0;
        return normal;
    }

    bool box::intersects(const ray r) const {
        vec3<double> pOs = position;
        vec3<double> pOr = r.getOrigin();
        vec3<double> vDr = r.getDirection();
        vec3<double> vLo = pOs - pOr;
        
        if (vec3<double>::dot(vLo, vDr) < 0) return false;
        
        double t0X = (corner0.getX() - r.getOrigin().getX()) / r.getDirection().getX();
        double t1X = (corner1.getX() - r.getOrigin().getX()) / r.getDirection().getX();
        double tMinX, tMaxX;
        if (t0X < t1X) {
            tMinX = t0X;
            tMaxX = t1X;
        } else {
            tMinX = t1X;
            tMaxX = t0X;
        }
        
        double t0Y = (corner0.getY() - r.getOrigin().getY()) / r.getDirection().getY();
        double t1Y = (corner1.getY() - r.getOrigin().getY()) / r.getDirection().getY();
        double tMinY, tMaxY;
        if (t0Y < t1Y) {
            tMinY = t0Y;
            tMaxY = t1Y;
        } else {
            tMinY = t1Y;
            tMaxY = t0Y;
        }
        
        if (tMinX > tMaxY || tMinY > tMaxX) return false;
        
        double t0Z = (corner0.getZ() - r.getOrigin().getZ()) / r.getDirection().getZ();
        double t1Z = (corner1.getZ() - r.getOrigin().getZ()) / r.getDirection().getZ();
        double tMinZ, tMaxZ;
        if (t0Z < t1Z) {
            tMinZ = t0Z;
            tMaxZ = t1Z;
        } else {
            tMinZ = t1Z;
            tMaxZ = t0Z;
        }
        
        if (tMinX > tMaxZ || tMinZ > tMaxX) return false;
        
        return true;
        
    }

    bool box::encloses(const vec3<double> point) const {
        return (point.getX() > corner0.getX() && point.getX() < corner1.getX()) &&
            (point.getY() > corner0.getY() && point.getY() < corner1.getY()) &&
            (point.getZ() > corner0.getZ() && point.getZ() < corner1.getZ());
    }
}
