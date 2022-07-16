//
//  color.hpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 22/3/2022.
//

#ifndef color_hpp
#define color_hpp

#include <ostream>
#include <cmath>

namespace math {

    class color {
    public:
        color(double r = 0.0, double g = 0.0, double b = 0.0, double a = 1.0);
        
        color& clamp();
        color& gammaCorrect();
        
        double getR() const;
        double getG() const;
        double getB() const;
        double getA() const;
        
        void setR(double r);
        void setG(double g);
        void setB(double b);
        void setA(double a);
        
        color operator +(const color&) const;
        color operator -(const color&) const;
        color operator *(const color&) const;
        color operator /(const color&) const;
        color& operator +=(const color&);
        color& operator -=(const color&);
        color& operator *=(const color&);
        color& operator /=(const color&);
        bool operator ==(const color&) const;
        bool operator !=(const color&) const;
        
        color operator *(const double& c) const;
        color operator /(const double& c) const;
        color& operator *=(const double& c);
        color& operator /=(const double& c);
        
        friend color operator *(const double& c, color& a) {
            return {a.r * c, a.g * c, a.b * c, a.a};
        }
        friend color operator /(const double& c, color& a) {
            return {a.r / c, a.g / c, a.b / c, a.a};
        }
        friend std::ostream& operator <<(std::ostream& os, const color& a) {
            return os << "color(" << a.r << ", " << a.g << ", " << a.b << ", " << a.a << ")";
        }
    private:
        double r, g, b, a;
    };
}

#endif /* color_hpp */
