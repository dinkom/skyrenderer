template <typename T>
bool solveQuadraticEquation(T a, T b, T c, T &x1, T &x2)
{
    if (b == 0) {
        if (a == 0) return false;
        x1 = 0; x2 = sqrt(-c/a);
        return true;
    }
    T discr = b * b - 4 * a * c;
    if (discr < 0) return false;
    T q = (b < 0) ? -0.5 * (b - sqrt(discr)) : -0.5 * (b + sqrt(discr));
    x1 = q / a;
    x2 = c / q;
    return true;
}

template<typename T>
bool intersect(const Ray<T> &r, const T &radius, T &t0, T &t1)
{
    Vec3<T> vec = r.origin;
    T A = r.direction.x * r.direction.x + r.direction.y * r.direction.y + r.direction.z * r.direction.z;
    T B = 2 * (r.direction.x * vec.x +  r.direction.y * vec.y + r.direction.z * vec.z);
    T C = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z - radius * radius;
    if (!solveQuadraticEquation(A, B, C, t0, t1)) return false;
    if (t0 > t1) std::swap(t0, t1);
    return true;
}

struct ControlValues
{
    ControlValues() : minRayleigh(10), maxRayleigh(std::numeric_limits<int>::max()), defaultRayleigh(10000),
                      minMie(10), maxMie(std::numeric_limits<int>::max()), defaultMie(2000),
                      minAngle(-115), maxAngle(115), defaultAngle(90)
    {}

    int minRayleigh;
    int maxRayleigh;
    int defaultRayleigh;
    int minMie;
    int maxMie;
    int defaultMie;
    int minAngle;
    int maxAngle;
    int defaultAngle;
};
