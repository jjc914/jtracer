#ifndef vec3_hpp
#define vec3_hpp

#include <cmath>
#include <ostream>

namespace math {

    template <typename T>
    class vec3 {
    public:
        vec3<T>(T x = 0, T y = 0, T z = 0);
        
        vec3<T>& normalize();
        
        T getX() const;
        T getY() const;
        T getZ() const;
        
        void setX(T x);
        void setY(T y);
        void setZ(T z);
        
        double getMagnitude() const;
        
        vec3<T> operator +(const vec3<T>& a) const;
        vec3<T> operator -(const vec3<T>& a) const;
        vec3<T>& operator +=(const vec3<T>& a);
        vec3<T>& operator -=(const vec3<T>& a);
        bool operator ==(const vec3<T>& a) const;
        bool operator !=(const vec3<T>& a) const;
        
        vec3<T> operator *(const T c) const;
        vec3<T> operator /(const T c) const;
        vec3<T>& operator *=(const T c);
        vec3<T>& operator /=(const T c);
        
        friend vec3<T> operator *(const T c, const vec3<T>& a) {
            return {a.x * c, a.y * c, a.z * c};
        }

        friend std::ostream& operator <<(std::ostream& os, const vec3<T>& a) {
            return os << "vec3(" << a.x << ", " << a.y << ", " << a.z << ")";
        }
        
        static vec3<T> cross(const vec3<T>& a, const vec3<T>& b);
        static double dot(const vec3<T>& a, const vec3<T>& b);
        static double distance(const vec3<T>& a, const vec3<T>& b);
        static vec3<T> reflect(const vec3<T>& d, const vec3<T>& n);
    private:
        T x, y, z;
        double magnitude;
        
        void recalculateMagnitude();
    };

    extern template class vec3<int>;
    extern template class vec3<float>;
    extern template class vec3<double>;
}
#endif