#include "vec3d.h"

template<typename T>
class Ray
{
public:
    Vec3<T> origin, direction;
    mutable T tmin, tmax;
    unsigned triangleId;
    int sign[3];
    Ray(Vec3<T> origin, Vec3<T> direction, T near = 0, T far = std::numeric_limits<T>::max()) :
        origin(origin), direction(direction), tmin(near), tmax(far)
    {}
    Vec3<T> operator () (const T &t) const
    { return origin + direction * t; }
};

