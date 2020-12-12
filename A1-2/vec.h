#pragma once
#include <array>

using namespace std;

namespace my
{
    template <typename T, int N>
    class Vec
    {

    public:
        Vec(array<T, N> const &v);

        array<T, N> vecarray() const { return vecarray_; }

        void set_vecarray(array<T, N> vecarray);

        T operator[](int arrayIndex) const;

        T &operator[](int arrayIndex);

        bool operator==(const Vec rhs) const;

        bool operator!=(const Vec rhs) const;

        Vec &operator+=(const Vec &rhs);

        Vec operator+(const Vec &rhs) const;

        Vec operator-() const;

    private:
        array<T, N> vecarray_;
    };

    template <typename T, int N>
    Vec<T, N>::Vec(array<T, N> const &v)
        : vecarray_(v) {}

    // Subscript read
    template <typename T, int N>
    T Vec<T, N>::operator[](int arrayIndex) const
    {
        return vecarray_[arrayIndex];
    }

    // Subscript write
    template <typename T, int N>
    T &Vec<T, N>::operator[](int arrayIndex)
    {
        return vecarray_[arrayIndex];
    }

    template <typename T, int N>
    bool Vec<T, N>::operator==(const Vec<T, N> rhs) const
    {
        return (this->vecarray_[0] == rhs[0] && this->vecarray_[1] == rhs[1] && this->vecarray_[2] == rhs[2]);
    }

    template <typename T, int N>
    bool Vec<T, N>::operator!=(const Vec<T, N> rhs) const
    {
        return !(this->vecarray_[0] == rhs[0] && this->vecarray_[1] == rhs[1] && this->vecarray_[2] == rhs[2]);
    }

    template <typename T, int N>
    Vec<T, N> &Vec<T, N>::operator+=(const Vec<T, N> &rhs)
    {
        this->vecarray_[0] += rhs.vecarray_[0];
        this->vecarray_[1] += rhs.vecarray_[1];
        this->vecarray_[2] += rhs.vecarray_[2];
        return *this;
    }

    template <typename T, int N>
    Vec<T, N> Vec<T, N>::operator+(const Vec<T, N> &rhs) const
    {
        Vec<T, N> temp(*this);
        temp += rhs;
        return temp;
    }
    template <typename T, int N>
    Vec<T, N> Vec<T, N>::operator-() const
    {
        Vec<T, N> temp(*this);
        temp[0] = -vecarray_[0];
        temp[1] = -vecarray_[1];
        temp[2] = -vecarray_[2];
        return temp;
    }
    template <typename T, int N>
    T dot(const Vec<T, N> &lhs, const Vec<T, N> &rhs)
    {
        T product = 0;
        for (int i = 0; i < lhs.vecarray().size(); i++)
        {
            product = product + lhs[i] * rhs[i];
        }
        return product;
    }

}; // namespace my