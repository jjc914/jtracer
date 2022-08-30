#include "vec2.hpp"

namespace math {

    template <typename T>
    vec2<T>::vec2(T x, T y) : x(x), y(y) {
        this->recalculateMagnitude();
    }

    template <typename T>
    vec2<T>& vec2<T>::normalize() {
        *this /= magnitude;
        magnitude = 1.0;
        return *this;
    }

    template <typename T>
    T vec2<T>::getX() const {
        return x;
    }

    template <typename T>
    T vec2<T>::getY() const {
        return y;
    }

    template <typename T>
    void vec2<T>::setX(T x) {
        this->x = x;
        recalculateMagnitude();
    }

    template <typename T>
    void vec2<T>::setY(T y) {
        this->y = y;
        recalculateMagnitude();
    }
    
    template <typename T>
    double vec2<T>::getMagnitude() const {
        return magnitude;
    }

    template <typename T>
    void vec2<T>::recalculateMagnitude() {
        magnitude = sqrt(x * x + y * y);
    }

    template <typename T>
    vec2<T> vec2<T>::operator +(const vec2<T>& a) const {
        return {x + a.x, y + a.y};
    }

    template <typename T>
    vec2<T> vec2<T>::operator -(const vec2<T>& a) const {
        return {x - a.x, y - a.y};
    }

    template <typename T>
    vec2<T>& vec2<T>::operator +=(const vec2<T>& a) {
        x += a.x;
        y += a.y;
        return *this;
    }

    template <typename T>
    vec2<T>& vec2<T>::operator -=(const vec2<T>& a) {
        x -= a.x;
        y -= a.y;
        return *this;
    }

    template <typename T>
    bool vec2<T>::operator ==(const vec2<T>& a) const {
        return x == a.x && y == a.y;
    }

    template <typename T>
    bool vec2<T>::operator !=(const vec2<T>& a) const {
        return x != a.x || y != a.y;
    }

    template <typename T>
    vec2<T> vec2<T>::operator *(const T c) const {
        return {x * c, y * c};
    }

    template <typename T>
    vec2<T> vec2<T>::operator /(const T c) const {
        return {x / c, y / c};
    }

    template <typename T>
    vec2<T>& vec2<T>::operator *=(const T c) {
        x *= c;
        y *= c;
        return *this;
    }

    template <typename T>
    vec2<T>& vec2<T>::operator /=(const T c) {
        x /= c;
        y /= c;
        return *this;
    }

    template <typename T>
    std::ostream& operator <<(std::ostream& os, const vec2<T>& a) {
        return os << "vec2(" << a.x << ", " << a.y << ")";
    }

    template <typename T>
    double dot(const vec2<T>& a, const vec2<T>& b) {
        return a.getX() * b.getX() + a.getY() * b.getY();
    }

    template <typename T>
    double vec2<T>::distance(const vec2<T>& a, const vec2<T>& b) {
        return sqrt((a.getX() - b.getX()) * (a.getX() - b.getX()) +
                    (a.getY() - b.getY()) * (a.getY() - b.getY()));
    }

    template class vec2<int>;
    template class vec2<float>;
    template class vec2<double>;
}