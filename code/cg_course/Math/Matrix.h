#ifndef CG_COURSE_MATRIX_H
#define CG_COURSE_MATRIX_H

#include <initializer_list>
#include <utility>
#include <array>


template<typename T, std::size_t N, std::size_t M>
class Matrix
{
public:
    Matrix();

    Matrix(const Matrix<T, N, M> &other);

    Matrix(Matrix<T, N, M> &&other) noexcept;

    Matrix(std::initializer_list<T> list);

    Matrix<T, N, M> &operator=(const Matrix<T, N, M> &other);

    Matrix<T, N, M> &operator=(Matrix<T, N, M> &&other);

    Matrix<T, N, M> &operator=(std::initializer_list<T> list);

    Matrix<T, N, M> operator+(const Matrix<T, N, M> &other) const;

    template<std::size_t K>
    Matrix<T, N, K> operator*(const Matrix<T, M, K> &other) const;

    Matrix<T, N, M> &operator+=(const Matrix<T, N, M> &other);

    const std::array<T, M> &operator[](int i) const;

    std::array<T, M> &operator[](int i);

    std::size_t rows() const;

    std::size_t columns() const;

private:
    std::array<std::array<T, M>, N> mtr;
};

using Matix4x3d = Matrix<double, 4, 3>;
using Matix4x4d = Matrix<double, 4, 4>;
template<std::size_t M>
using RowMatrixd = Matrix<double, 1, M>;
template<std::size_t N>
using ColumnMatrixd = Matrix<double, N, 1>;

template<typename T, std::size_t N, std::size_t M>
Matrix<T, N, M>::Matrix()
{
    mtr.fill({});
}

template<typename T, std::size_t N, std::size_t M>
Matrix<T, N, M>::Matrix(const Matrix<T, N, M> &other) : mtr(other.mtr)
{

}

template<typename T, std::size_t N, std::size_t M>
Matrix<T, N, M>::Matrix(Matrix<T, N, M> &&other) noexcept : mtr(std::move(other.mtr))
{

}

template<typename T, std::size_t N, std::size_t M>
Matrix<T, N, M>::Matrix(std::initializer_list<T> list)
{
    auto it = list.begin();
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            mtr[i][j] = *(it++);
}

template<typename T, std::size_t N, std::size_t M>
Matrix<T, N, M> &Matrix<T, N, M>::operator=(const Matrix<T, N, M> &other)
{
    mtr = other.mtr;
    return *this;
}

template<typename T, std::size_t N, std::size_t M>
Matrix<T, N, M> &Matrix<T, N, M>::operator=(Matrix<T, N, M> &&other)
{
    mtr = std::move(other.mtr);
    return *this;
}

template<typename T, std::size_t N, std::size_t M>
Matrix<T, N, M> &Matrix<T, N, M>::operator=(std::initializer_list<T> list)
{
    return Matrix<T, N, M>(list);
}

template<typename T, std::size_t N, std::size_t M>
Matrix<T, N, M> Matrix<T, N, M>::operator+(const Matrix<T, N, M> &other) const
{
    return Matrix<T, N, M>(*this) += other;
}

template<typename T, std::size_t N, std::size_t M>
template<std::size_t K>
Matrix<T, N, K> Matrix<T, N, M>::operator*(const Matrix<T, M, K> &other) const
{
    Matrix<T, N, K> product;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < K; j++)
            for (int k = 0; k < M; k++)
                product[i][j] += mtr[i][k] * other[k][j];

    return product;
}

template<typename T, std::size_t N, std::size_t M>
Matrix<T, N, M> &Matrix<T, N, M>::operator+=(const Matrix<T, N, M> &other)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            mtr[i][j] += other.mtr[i][j];

    return *this;
}

template<typename T, std::size_t N, std::size_t M>
const std::array<T, M> &Matrix<T, N, M>::operator[](int i) const
{
    return mtr[i];
}

template<typename T, std::size_t N, std::size_t M>
std::array<T, M> &Matrix<T, N, M>::operator[](int i)
{
    return mtr[i];
}

template<typename T, std::size_t N, std::size_t M>
std::size_t Matrix<T, N, M>::rows() const
{
    return N;
}

template<typename T, std::size_t N, std::size_t M>
std::size_t Matrix<T, N, M>::columns() const
{
    return M;
}

#endif

