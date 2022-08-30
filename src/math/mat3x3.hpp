#ifndef mat3x3_hpp
#define mat3x3_hpp

#include <ostream>

#include "vec3.hpp"

namespace math {

    template <typename T>
    class mat3x3 {
    public:
        mat3x3<T>(T a1 = 1, T a2 = 0, T a3 = 0,
                  T b1 = 0, T b2 = 1, T b3 = 0,
                  T c1 = 0, T c2 = 0, T c3 = 1);
        
        mat3x3<T> transpose() const;
        T determinant() const;
        mat3x3<T> inverse() const;
        
        T get(int y, int x) const;

        void set(int y, int x, T val);

        mat3x3<T> operator +(const mat3x3<T>& a) const;
        mat3x3<T> operator -(const mat3x3<T>& a) const;
        mat3x3<T>& operator +=(const mat3x3<T>& a);
        mat3x3<T>& operator -=(const mat3x3<T>& a);
        bool operator ==(const mat3x3<T>& a) const;
        bool operator !=(const mat3x3<T>& a) const;

        mat3x3<T> operator *(const T c) const;
        mat3x3<T> operator /(const T c) const;
        mat3x3<T>& operator *=(const T c);
        mat3x3<T>& operator /=(const T c);

        friend mat3x3<T> operator *(const T c, const mat3x3<T>& a) {
            return {a.values[0][0] * c, a.values[0][1] * c, a.values[0][2] * c,
                    a.values[1][0] * c, a.values[1][1] * c, a.values[1][2] * c,
                    a.values[2][0] * c, a.values[2][1] * c, a.values[2][2] * c};
        }

        mat3x3<T> operator *(const mat3x3<T> a) const;
        mat3x3<T>& operator *=(const mat3x3<T> c);

        vec3<T> operator *(const vec3<T> a) const;

        friend vec3<T> operator *(const vec3<T> a, const mat3x3<T>& b) {
            return {b.values[0][0] * a.getX() + b.values[1][0] * a.getY() + b.values[2][0] * a.getZ(), 
                    b.values[0][1] * a.getX() + b.values[1][1] * a.getY() + b.values[2][1] * a.getZ(), 
                    b.values[0][2] * a.getX() + b.values[1][2] * a.getY() + b.values[2][2] * a.getZ()};
        }
        friend vec3<T>& operator *=(vec3<T>& a, const mat3x3<T> b) {
            double x = b.values[0][0] * a.getX() + b.values[1][0] * a.getY() + b.values[2][0] * a.getZ();
            double y = b.values[0][1] * a.getX() + b.values[1][1] * a.getY() + b.values[2][1] * a.getZ();
            double z = b.values[0][2] * a.getX() + b.values[1][2] * a.getY() + b.values[2][2] * a.getZ();
            a.setX(x);
            a.setY(y);
            a.setZ(z);
            return a;
        }

        friend std::ostream& operator <<(std::ostream& os, const mat3x3<T>& a) {
            return os << "mat3x3(" << 
                   a.values[0][0] << ", " << a.values[0][1] << ", " << a.values[0][2] << ", " <<
                   a.values[1][0] << ", " << a.values[1][1] << ", " << a.values[1][2] << ", " <<
                   a.values[2][0] << ", " << a.values[2][1] << ", " << a.values[2][2] << ")";
        }

        static mat3x3<T> skew(const vec3<T>& a);
        static mat3x3<T> align(const vec3<T>& a, const vec3<T>& b);
        static vec3<T> rotate(const vec3<T>& a, const vec3<T>& axis, const double t);
    private:
        T values[3][3];
    };

    extern template class mat3x3<int>;
    extern template class mat3x3<float>;
    extern template class mat3x3<double>;
}
#endif