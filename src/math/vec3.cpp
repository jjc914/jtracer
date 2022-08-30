#include "vec3.hpp"

namespace math {

    template <typename T>
    vec3<T>::vec3(T x, T y, T z) : x(x), y(y), z(z) {
        this->recalculateMagnitude();
    }

    template <typename T>
    vec3<T>& vec3<T>::normalize() {
        *this /= magnitude;
        magnitude = 1.0;
        return *this;
    }

    template <typename T>
    T vec3<T>::getX() const {
        return x;
    }

    template <typename T>
    T vec3<T>::getY() const {
        return y;
    }

    template <typename T>
    T vec3<T>::getZ() const {
        return z;
    }

    template <typename T>
    void vec3<T>::setX(T x) {
        this->x = x;
        recalculateMagnitude();
    }

    template <typename T>
    void vec3<T>::setY(T y) {
        this->y = y;
        recalculateMagnitude();
    }

    template <typename T>
    void vec3<T>::setZ(T z) {
        this->z = z;
        recalculateMagnitude();
    }
    
    template <typename T>
    double vec3<T>::getMagnitude() const {
        return magnitude;
    }

    template <typename T>
    void vec3<T>::recalculateMagnitude() {
        magnitude = sqrt(x * x + y * y + z * z);
    }

    template <typename T>
    vec3<T> vec3<T>::operator +(const vec3<T>& a) const {
        return {x + a.x, y + a.y, z + a.z};
    }

    template <typename T>
    vec3<T> vec3<T>::operator -(const vec3<T>& a) const {
        return {x - a.x, y - a.y, z - a.z};
    }

    template <typename T>
    vec3<T>& vec3<T>::operator +=(const vec3<T>& a) {
        x += a.x;
        y += a.y;
        z += a.z;
        return *this;
    }

    template <typename T>
    vec3<T>& vec3<T>::operator -=(const vec3<T>& a) {
        x -= a.x;
        y -= a.y;
        z -= a.z;
        return *this;
    }

    template <typename T>
    bool vec3<T>::operator ==(const vec3<T>& a) const {
        return x == a.x && y == a.y && z == a.z;
    }

    template <typename T>
    bool vec3<T>::operator !=(const vec3<T>& a) const {
        return x != a.x || y != a.y || z != a.z;
    }

    template <typename T>
    vec3<T> vec3<T>::operator *(const T c) const {
        return {x * c, y * c, z * c};
    }

    template <typename T>
    vec3<T> vec3<T>::operator /(const T c) const {
        return {x / c, y / c, z / c};
    }

    template <typename T>
    vec3<T>& vec3<T>::operator *=(const T c) {
        x *= c;
        y *= c;
        z *= c;
        return *this;
    }

    template <typename T>
    vec3<T>& vec3<T>::operator /=(const T c) {
        x /= c;
        y /= c;
        z /= c;
        return *this;
    }

    template <typename T>
    std::ostream& operator <<(std::ostream& os, const vec3<T>& a) {
        return os << "vec3(" << a.x << ", " << a.y << ", " << a.z << ")";
    }

    template <typename T>
    vec3<T> vec3<T>::cross(const vec3<T>& a, const vec3<T>& b) {
        return {
            a.getY() * b.getZ() - a.getZ() * b.getY(),
            a.getZ() * b.getX() - a.getX() * b.getZ(),
            a.getX() * b.getY() - a.getY() * b.getX()
        };
    }

    template <typename T>
    double vec3<T>::dot(const vec3<T>& a, const vec3<T>& b) {
        return a.getX() * b.getX() + a.getY() * b.getY() + a.getZ() * b.getZ();
    }

    template <typename T>
    double vec3<T>::distance(const vec3<T>& a, const vec3<T>& b) {
        return sqrt(
                    (a.getX() - b.getX()) * (a.getX() - b.getX()) +
                    (a.getY() - b.getY()) * (a.getY() - b.getY()) +
                    (a.getZ() - b.getZ()) * (a.getZ() - b.getZ())
                    );
    }

    template <typename T>
    vec3<T> vec3<T>::reflect(const vec3<T>& d, const vec3<T>& n) {
        return d - 2 * (vec3<T>::dot(d, n) / (d.getMagnitude() * n.getMagnitude())) * n;
    }

    template class vec3<int>;
    template class vec3<float>;
    template class vec3<double>;
}