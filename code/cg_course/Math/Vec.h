#ifndef CG_COURSE_VEC_H
#define CG_COURSE_VEC_H

#include <initializer_list>
#include <array>
#include <cmath>
#include <QColor>

#include "Errors.h"

template<typename T, std::size_t N>
class Vec
{
public:
    Vec();

    Vec(const Vec<T, N> &other);

    Vec(Vec<T, N> &&other) noexcept;

    Vec(std::initializer_list<T> list);

    Vec(QColor &color);

    Vec<T, N> &operator=(const Vec<T, N> &other);

    Vec<T, N> &operator=(Vec<T, N> &&other) noexcept;

    Vec<T, N> operator+(const Vec<T, N> &other) const;

    Vec<T, N> operator-(const Vec<T, N> &other) const;

    Vec<T, N> operator-() const;

    Vec<T, N> operator*(const T &n) const;

    Vec<T, N> operator/(const T &n) const;

    T operator&(const Vec<T, N> &other) const;

    Vec<T, N> operator^(const Vec<T, N> &other) const;

    Vec<T, N> &operator+=(const Vec<T, N> &other);

    Vec<T, N> &operator-=(const Vec<T, N> &other);

    Vec<T, N> &operator*=(const T &n);

    Vec<T, N> &operator/=(const T &n);

    const T &operator[](int i) const;

    T &operator[](int i);

    double len_sqr() const;

    T len() const;

    void norm();

    std::size_t size() const;

    operator QColor() const;

    Vec<T, N> &member_mult(const Vec<T, N> &other);

private:
    std::array<T, N> arr;
};

using Vec3d = Vec<double, 3>;
using Color = Vec<double, 3>;
using Point3d = Vec<double, 3>;
using Point4d = Vec<double, 4>;
using Vec4d = Vec<double, 4>;

template<typename T, std::size_t N>
Vec<T, N> operator*(const T &n, const Vec<T, N> &other)
{
    return other * n;
}

template<typename T, std::size_t N>
Vec<T, N>::Vec()
{
    arr.fill({});
}

template<typename T, std::size_t N>
Vec<T, N>::Vec(const Vec<T, N> &other) : arr(other.arr)
{

}

template<typename T, std::size_t N>
Vec<T, N>::Vec(Vec<T, N> &&other) noexcept: arr(std::move(other.arr))
{

}

template<typename T, std::size_t N>
Vec<T, N>::Vec(std::initializer_list<T> list)
{
    auto it = list.begin();

    for (int i = 0; i < N; i++)
        arr[i] = *(it++);
}

template<typename T, std::size_t N>
Vec<T, N>::Vec(QColor &color)
{
    arr[0] = color.red() / 255.0;
    arr[1] = color.green() / 255.0;
    arr[2] = color.blue() / 255.0;
}

template<typename T, std::size_t N>
Vec<T, N> &Vec<T, N>::operator=(const Vec<T, N> &other)
{
    arr = other.arr;
    return *this;
}

template<typename T, std::size_t N>
Vec<T, N> &Vec<T, N>::operator=(Vec<T, N> &&other) noexcept
{
    arr = std::move(other.arr);

    return *this;
}

template<typename T, std::size_t N>
Vec<T, N> Vec<T, N>::operator+(const Vec<T, N> &other) const
{
    return Vec<T, N>(*this) += other;
}

template<typename T, std::size_t N>
Vec<T, N> Vec<T, N>::operator-(const Vec<T, N> &other) const
{
    return Vec<T, N>(*this) -= other;
}

template<typename T, std::size_t N>
Vec<T, N> Vec<T, N>::operator-() const
{
    return *this * -1.0;
}

template<typename T, std::size_t N>
Vec<T, N> Vec<T, N>::operator*(const T &n) const
{
    return Vec<T, N>(*this) *= n;
}

template<typename T, std::size_t N>
Vec<T, N> Vec<T, N>::operator/(const T &n) const
{
    return Vec<T, N>(*this) /= n;
}

template<typename T, std::size_t N>
T Vec<T, N>::operator&(const Vec<T, N> &other) const
{
    T res = {};

    for (int i = 0; i < N; i++)
        res += arr[i] * other.arr[i];

    return res;
}

template<typename T, std::size_t N>
Vec<T, N> Vec<T, N>::operator^(const Vec<T, N> &other) const
{
    if (N != 3)
        throw DimensionError(__FILE__, __FUNCTION__, __LINE__,
                             "For a vector product , vectors of dimension 3 are needed");
    Vec<T, N> product;

    product[0] = arr[1] * other.arr[2] - arr[2] * other.arr[1];
    product[1] = arr[2] * other.arr[0] - arr[0] * other.arr[2];
    product[2] = arr[0] * other.arr[1] - arr[1] * other.arr[0];

    return product;
}

template<typename T, std::size_t N>
Vec<T, N> &Vec<T, N>::operator+=(const Vec<T, N> &other)
{
    for (int i = 0; i < N; i++)
        arr[i] += other.arr[i];

    return *this;
}

template<typename T, std::size_t N>
Vec<T, N> &Vec<T, N>::operator-=(const Vec<T, N> &other)
{
    for (int i = 0; i < N; i++)
        arr[i] -= other.arr[i];

    return *this;
}

template<typename T, std::size_t N>
Vec<T, N> &Vec<T, N>::operator*=(const T &n)
{
    for (int i = 0; i < N; i++)
        arr[i] *= n;

    return *this;
}

template<typename T, std::size_t N>
Vec<T, N> &Vec<T, N>::operator/=(const T &n)
{
    for (int i = 0; i < N; i++)
        arr[i] /= n;

    return *this;
}

template<typename T, std::size_t N>
const T &Vec<T, N>::operator[](int i) const
{
    return arr[i];
}

template<typename T, std::size_t N>
T &Vec<T, N>::operator[](int i)
{
    return arr[i];
}

template<typename T, std::size_t N>
double Vec<T, N>::len_sqr() const
{
    T sum = {};

    for (auto &it: arr)
        sum += it * it;

    return sum;
}

template<typename T, std::size_t N>
T Vec<T, N>::len() const
{
    return sqrt(len_sqr());
}

template<typename T, std::size_t N>
void Vec<T, N>::norm()
{
    T l = this->len();

    for (auto &it: arr)
        it /= l;
}

template<typename T, std::size_t N>
std::size_t Vec<T, N>::size() const
{
    return N;
}

template<typename T, std::size_t N>
Vec<T, N>::operator QColor() const
{
    if (N != 3)
        throw DimensionError(__FILE__, __FUNCTION__, __LINE__,
                             "Can't cast to QColor, vectors of dimension 3 are needed");

    QColor res(min(1.0, arr[0]) * 255.0,
               min(1.0, arr[1]) * 255.0,
               min(1.0, arr[2]) * 255.0
    );

//    QColor res(arr[0] * 255.0, arr[1] * 255.0, arr[2] * 255.0);
//    QColor res(100, 100, 100);


    return res;
}

template<typename T, std::size_t N>
Vec<T, N> &Vec<T, N>::member_mult(const Vec<T, N> &other)
{
    for (int i = 0; i < N; i++)
        this->arr[i] *= other.arr[i];

    return *this;
}

#endif
