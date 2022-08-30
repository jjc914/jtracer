#include "mat3x3.hpp"

namespace math {

    template <typename T>
    mat3x3<T>::mat3x3(T a1, T a2, T a3, 
                      T b1, T b2, T b3,
                      T c1, T c2, T c3) {
        values[0][0] = a1;
        values[0][1] = a2;
        values[0][2] = a3;
        values[1][0] = b1;
        values[1][1] = b2;
        values[1][2] = b3;
        values[2][0] = c1;
        values[2][1] = c2;
        values[2][2] = c3;
    }

    template <typename T>
    mat3x3<T> mat3x3<T>::transpose() const {
        return {values[0][0], values[1][0], values[2][0], 
                values[0][1], values[1][1], values[2][1], 
                values[0][2], values[1][2], values[2][2]};
    }

    template <typename T>
    T mat3x3<T>::determinant() const {
        return values[0][0] * (values[1][1] * values[2][2] - values[2][1] * values[1][2]) - values[1][0] * (values[0][1] * values[2][2] - values[2][1] * values[0][2]) + values[2][0] * (values[0][1] * values[1][2] - values[1][1] * values[0][2]);
    }

    template <typename T>
    mat3x3<T> mat3x3<T>::inverse() const {
        return mat3x3<T>(values[1][1] * values[2][2] - values[1][2] * values[2][1], values[0][2] * values[2][1] - values[0][1] * values[2][2], values[0][1] * values[1][2] - values[0][2] * values[1][1], 
                         values[1][2] * values[2][0] - values[1][0] * values[2][2], values[0][0] * values[2][2] - values[0][2] * values[2][0], values[0][2] * values[1][0] - values[0][0] * values[1][2], 
                         values[1][0] * values[2][1] - values[1][1] * values[2][0], values[0][1] * values[2][0] - values[0][0] * values[2][1], values[0][0] * values[1][1] - values[0][1] * values[1][0]) / determinant();
    }

    template <typename T>
    T mat3x3<T>::get(int y, int x) const {
        return values[y][x];
    }

    template <typename T>
    void mat3x3<T>::set(int y, int x, T val) {
        values[y][x] = val;
    }

    template <typename T>
    mat3x3<T> mat3x3<T>::operator +(const mat3x3<T>& a) const {
        return {values[0][0] + a.values[0][0], values[0][1] + a.values[0][1], values[0][2] + a.values[0][2],
                values[1][0] + a.values[1][0], values[1][1] + a.values[1][1], values[1][2] + a.values[1][2],
                values[2][0] + a.values[2][0], values[2][1] + a.values[2][1], values[2][2] + a.values[2][2]};
    }

    template <typename T>
    mat3x3<T> mat3x3<T>::operator -(const mat3x3<T>& a) const {
        return {values[0][0] - a.values[0][0], values[0][1] - a.values[0][1], values[0][2] - a.values[0][2],
                values[1][0] - a.values[1][0], values[1][1] - a.values[1][1], values[1][2] - a.values[1][2],
                values[2][0] - a.values[2][0], values[2][1] - a.values[2][1], values[2][2] - a.values[2][2]};
    }

    template <typename T>
    mat3x3<T>& mat3x3<T>::operator +=(const mat3x3<T>& a) {
        values[0][0] += a.values[0][0];
        values[0][1] += a.values[0][1];
        values[0][2] += a.values[0][2];
        values[1][0] += a.values[1][0];
        values[1][1] += a.values[1][1];
        values[1][2] += a.values[1][2];
        values[2][0] += a.values[2][0];
        values[2][1] += a.values[2][1];
        values[2][2] += a.values[2][2];
        return *this;
    }

    template <typename T>
    mat3x3<T>& mat3x3<T>::operator -=(const mat3x3<T>& a) {
        values[0][0] -= a.values[0][0];
        values[0][1] -= a.values[0][1];
        values[0][2] -= a.values[0][2];
        values[1][0] -= a.values[1][0];
        values[1][1] -= a.values[1][1];
        values[1][2] -= a.values[1][2];
        values[2][0] -= a.values[2][0];
        values[2][1] -= a.values[2][1];
        values[2][2] -= a.values[2][2];
        return *this;
    }

    template <typename T>
    bool mat3x3<T>::operator ==(const mat3x3<T>& a) const {
        return values[0][0] == a.values[0][0] && values[0][1] == a.values[0][1] && values[0][2] == a.values[0][2] &&
               values[1][0] == a.values[1][0] && values[1][1] == a.values[1][1] && values[1][2] == a.values[1][2] &&
               values[2][0] == a.values[2][0] && values[2][1] == a.values[2][1] && values[2][2] == a.values[2][2];
    }

    template <typename T>
    bool mat3x3<T>::operator !=(const mat3x3<T>& a) const {
        return values[0][0] != a.values[0][0] || values[0][1] != a.values[0][1] || values[0][2] != a.values[0][2] ||
               values[1][0] != a.values[1][0] || values[1][1] != a.values[1][1] || values[1][2] != a.values[1][2] ||
               values[2][0] != a.values[2][0] || values[2][1] != a.values[2][1] || values[2][2] != a.values[2][2];
    }

    template <typename T>
    mat3x3<T> mat3x3<T>::operator *(const T c) const {
        return {values[0][0] * c, values[0][1] * c, values[0][2] * c,
                values[1][0] * c, values[1][1] * c, values[1][2] * c,
                values[2][0] * c, values[2][1] * c, values[2][2] * c};
    }

    template <typename T>
    mat3x3<T> mat3x3<T>::operator /(const T c) const {
        return {values[0][0] / c, values[0][1] / c, values[0][2] / c,
                values[1][0] / c, values[1][1] / c, values[1][2] / c,
                values[2][0] / c, values[2][1] / c, values[2][2] / c};
    }

    template <typename T>
    mat3x3<T>& mat3x3<T>::operator *=(const T c) {
        values[0][0] *= c;
        values[0][1] *= c;
        values[0][2] *= c;
        values[1][0] *= c;
        values[1][1] *= c;
        values[1][2] *= c;
        values[2][0] *= c;
        values[2][1] *= c;
        values[2][2] *= c;
        return *this;
    }

    template <typename T>
    mat3x3<T>& mat3x3<T>::operator /=(const T c) {
        values[0][0] /= c;
        values[0][1] /= c;
        values[0][2] /= c;
        values[1][0] /= c;
        values[1][1] /= c;
        values[1][2] /= c;
        values[2][0] /= c;
        values[2][1] /= c;
        values[2][2] /= c;
        return *this;
    }

    template <typename T>
    mat3x3<T> mat3x3<T>::operator *(const mat3x3<T> a) const {
        return {values[0][0] * a.values[0][0] + values[0][1] * a.values[1][0] + values[0][2] * a.values[2][0], values[0][0] * a.values[0][1] + values[0][1] * a.values[1][1] + values[0][2] * a.values[2][1], values[0][0] * a.values[0][2] + values[0][1] * a.values[1][2] + values[0][2] * a.values[2][2],
                values[1][0] * a.values[0][0] + values[1][1] * a.values[1][0] + values[1][2] * a.values[2][0], values[1][0] * a.values[0][1] + values[1][1] * a.values[1][1] + values[1][2] * a.values[2][1], values[1][0] * a.values[0][2] + values[1][1] * a.values[1][2] + values[1][2] * a.values[2][2],
                values[2][0] * a.values[0][0] + values[2][1] * a.values[1][0] + values[2][2] * a.values[2][0], values[2][0] * a.values[0][1] + values[2][1] * a.values[1][1] + values[2][2] * a.values[2][1], values[2][0] * a.values[0][2] + values[2][1] * a.values[1][2] + values[2][2] * a.values[2][2]};
    }

    template <typename T>
    mat3x3<T>& mat3x3<T>::operator *=(const mat3x3<T> a) {
        double a1 = values[0][0] * a.values[0][0] + values[0][1] * a.values[1][0] + values[0][2] * a.values[2][0];
        double a2 = values[0][0] * a.values[0][1] + values[0][1] * a.values[1][1] + values[0][2] * a.values[2][1];
        double a3 = values[0][0] * a.values[0][2] + values[0][1] * a.values[1][2] + values[0][2] * a.values[2][2];
        double b1 = values[1][0] * a.values[0][0] + values[1][1] * a.values[1][0] + values[1][2] * a.values[2][0];
        double b2 = values[1][0] * a.values[0][1] + values[1][1] * a.values[1][1] + values[1][2] * a.values[2][1];
        double b3 = values[1][0] * a.values[0][2] + values[1][1] * a.values[1][2] + values[1][2] * a.values[2][2];
        double c1 = values[2][0] * a.values[0][0] + values[2][1] * a.values[1][0] + values[2][2] * a.values[2][0];
        double c2 = values[2][0] * a.values[0][1] + values[2][1] * a.values[1][1] + values[2][2] * a.values[2][1];
        double c3 = values[2][0] * a.values[0][2] + values[2][1] * a.values[1][2] + values[2][2] * a.values[2][2];
        values[0][0] = a1;
        values[0][1] = a2;
        values[0][2] = a3;
        values[1][0] = b1;
        values[1][1] = b2;
        values[1][2] = b3;
        values[2][0] = c1;
        values[2][1] = c2;
        values[2][2] = c3;
        return *this;
    }

    template <typename T>
    vec3<T> mat3x3<T>::operator *(const vec3<T> a) const {
        return vec3<T>(values[0][0] * a.getX() + values[0][1] * a.getY() + values[0][2] * a.getZ(), 
                       values[1][0] * a.getX() + values[1][1] * a.getY() + values[1][2] * a.getZ(), 
                       values[2][0] * a.getX() + values[2][1] * a.getY() + values[2][2] * a.getZ());
    }

    template <typename T>
    mat3x3<T> mat3x3<T>::skew(const vec3<T>& a) {
        return {0,         -a.getZ(), a.getY(),
                a.getZ(),  0,         -a.getX(),
                -a.getY(), a.getX(), 0};
    }

    template <typename T>
    mat3x3<T> mat3x3<T>::align(const vec3<T>& a, const vec3<T>& b) {
        vec3<T> v = vec3<T>::cross(a, b);
        double s = v.getMagnitude();
        double c = vec3<T>::dot(a, b);
        mat3x3<T> skew = mat3x3<T>::skew(v);
        mat3x3<T> R = mat3x3<T>() + skew + ((skew * skew) / (1 + c));
        return R;
    }

    // FIXME: align not working?

    template <typename T>
    vec3<T> mat3x3<T>::rotate(const vec3<T>& a, const vec3<T>& axis, const double t) {
        mat3x3<T> R = mat3x3<T>::align(axis, vec3<T>(0.0, 1.0, 0.0));
        vec3<T> A = R * a;
        mat3x3<T> rot = mat3x3<T>(std::cos(t),  0,  std::sin(t),
                                  0,            1,  0,
                                  -std::sin(t), 0,  std::cos(t));
        A = rot * A;
        A = R.inverse() * A;
        return A;
    }

    template class mat3x3<int>;
    template class mat3x3<float>;
    template class mat3x3<double>;
}