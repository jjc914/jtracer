#ifndef vec2_hpp
#define vec2_hpp

#include <cmath>
#include <ostream>

namespace math {

    template <typename T>
    class vec2 {
    public:
        vec2<T>(T x = 0, T y = 0);
        
        vec2<T>& normalize();
        
        T getX() const;
        T getY() const;
        
        void setX(T x);
        void setY(T y);
        
        double getMagnitude() const;
        
        vec2<T> operator +(const vec2<T>& a) const;
        vec2<T> operator -(const vec2<T>& a) const;
        vec2<T>& operator +=(const vec2<T>& a);
        vec2<T>& operator -=(const vec2<T>& a);
        bool operator ==(const vec2<T>& a) const;
        bool operator !=(const vec2<T>& a) const;
        
        vec2<T> operator *(const T c) const;
        vec2<T> operator /(const T c) const;
        vec2<T>& operator *=(const T c);
        vec2<T>& operator /=(const T c);
        
        friend vec2<T> operator *(const T c, const vec2<T>& a) {
            return {a.getX() * c, a.getY() * c};
        }
        
        friend std::ostream& operator <<(std::ostream& os, const vec2<T>& a) {
            return os << "vec3(" << a.x << ", " << a.y << ")";
        }
        
        static double dot(const vec2<T>& a, const vec2<T>& b);
        static double distance(const vec2<T>& a, const vec2<T>& b);
    private:
        T x, y;
        double magnitude;
        
        void recalculateMagnitude();
    };

    extern template class vec2<int>;
    extern template class vec2<float>;
    extern template class vec2<double>;
}

#endif