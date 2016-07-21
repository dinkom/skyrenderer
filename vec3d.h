#include <iostream>
#include <limits>
#include <stdint.h>
#include <string.h>
#include <cmath>

template <typename T>
class Vec3
{
public:
    Vec3() : x(0), y(0), z(0) {}
    Vec3(float val) : x(val), y(val), z(val) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    T x, y, z;

    T & operator [] (int i) { return (&x)[i]; }
    Vec3 operator + (const Vec3<T> &v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3 operator * (const T &r) const { return Vec3(x * r, y * r, z * r); }
    Vec3 operator * (const Vec3<T> &v) const { return Vec3(x * v.x, y * v.y, z * v.z); }
    Vec3 & operator += (const Vec3<T> &v) { x += v.x, y += v.y, z += v.z; return *this; }
    Vec3 & operator *= (const Vec3<T> &v) { x *= v.x, y *= v.y, z *= v.z; return *this; }

    friend std::ostream & operator << (std::ostream &stream, const Vec3 &v)
    {
        stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return stream;
    }

    T length() const { return sqrtf(x * x + y * y + z * z); }
    T max() const { return std::max(x, std::max(y, z)); }

    T dot(const Vec3<T> &v) { return v.x * x + v.y * y + v.z * z; }

    Vec3 & normalize()
    {
        T len = x * x + y * y + z * z;
        if (len > 0) {
            T invLen = 1 / sqrt(len);
            x *= invLen, y *= invLen, z *= invLen;
        }
        return *this;
    }
};

typedef Vec3<float> Vec3f;
