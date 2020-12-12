#pragma once
#include <array>

using namespace std;

namespace my
{
    class Vec3f
    {
    public:
        Vec3f(float x = 0.0f, float y = 0.0f, float z = 0.0f);
        
        array<float, 3> vecarray() const { return vecarray_; }

        void set_vecarray(array<float, 3> vecarray);

        float operator[](int arrayIndex) const;

        float &operator[](int arrayIndex);

        friend bool operator==(const Vec3f &rhs, const Vec3f &lhs);

        friend bool operator!=(const Vec3f &rhs, const Vec3f &lhs);

        Vec3f &operator+=(const Vec3f &rhs);

        Vec3f operator+(const Vec3f &rhs) const;

        Vec3f operator-() const;

    private:
        array<float, 3> vecarray_;
    };

    float dot(const Vec3f &rhs, const Vec3f &lhs);

}; // namespace my