//
//  color.cpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 22/3/2022.
//

#include "color.hpp"

namespace math {

    color::color(double r, double g, double b, double a) : r(r), g(g), b(b), a(a){
        
    }

    double color::getR() const {
        return r;
    }

    double color::getG() const {
        return g;
    }

    double color::getB() const {
        return b;
    }

    double color::getA() const {
        return a;
    }

    void color::setR(double r) {
        this->r = r;
    }

    void color::setG(double g) {
        this->g = g;
    }

    void color::setB(double b) {
        this->b = b;
    }

    void color::setA(double a) {
        this->a = a;
    }

    color color::operator +(const color& c) const {
        return {r + c.r, g + c.g, b + c.b, a};
    }

    color color::operator -(const color& c) const {
        return {r - c.r, g - c.g, b - c.b, a};
    }

    color& color::operator +=(const color& c) {
        r += c.r;
        g += c.g;
        b += c.b;
        return *this;
    }

    color& color::operator -=(const color& c) {
        r -= c.r;
        g -= c.g;
        b -= c.b;
        return *this;
    }

    bool color::operator ==(const color& c) const {
        return r == c.r && g == c.g && b == c.b && a == c.a;
    }

    bool color::operator !=(const color& c) const {
        return r != c.r || g != c.g || b != c.b || a != c.a;
    }

    color color::operator *(const double& c) const {
        return {r * c, g * c, b * c, a};
    }

    color color::operator /(const double& c) const {
        return {r / c, g / c, b / c, a};
    }

    color& color::operator *=(const double& c) {
        r *= c;
        g *= c;
        b *= c;
        return *this;
    }

    color& color::operator /=(const double& c) {
        r /= c;
        g /= c;
        b /= c;
        return *this;
    }
}
