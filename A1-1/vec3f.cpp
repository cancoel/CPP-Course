#include "vec3f.h"

namespace my
{

    Vec3f::Vec3f(float x, float y, float z)
        : vecarray_{x, y, z}
    {
    }

    void Vec3f::set_vecarray(array<float, 3> vecarray)
    {
        vecarray_ = vecarray;
    }

    // Subscript read
    float Vec3f::operator[](int arrayIndex) const
    {
        return vecarray_[arrayIndex];
    }

    // Subscript write
    float &Vec3f::operator[](int arrayIndex)
    {
        return vecarray_[arrayIndex];
    }

    bool operator==(const Vec3f &rhs, const Vec3f &lhs)
    {
        return rhs[0] == lhs[0] && rhs[1] == lhs[1] && rhs[2] == lhs[2];
    }

    bool operator!=(const Vec3f &rhs, const Vec3f &lhs)
    {
        return !(rhs[0] == lhs[0] && rhs[1] == lhs[1] && rhs[2] == lhs[2]);
    }

    Vec3f &Vec3f::operator+=(const Vec3f &rhs)
    {
        this->vecarray_[0] += rhs.vecarray_[0];
        this->vecarray_[1] += rhs.vecarray_[1];
        this->vecarray_[2] += rhs.vecarray_[2];
        return *this;
    }

    Vec3f Vec3f::operator+(const Vec3f &rhs) const
    {
        Vec3f temp(*this);
        temp += rhs;
        return temp;
    }

    Vec3f Vec3f::operator-() const
    {
        Vec3f temp(*this);
        temp[0] = -vecarray_[0];
        temp[1] = -vecarray_[1];
        temp[2] = -vecarray_[2];
        return temp;
    }

    float dot(const Vec3f &rhs, const Vec3f &lhs)
    {
        float product = 0;
        for (int i = 0; i < rhs.vecarray().size(); i++)
        {
            product = product + rhs[i] * lhs[i];
        }
        return product;
    }

}; // namespace my
