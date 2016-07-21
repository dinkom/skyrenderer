#include <QString>
#include "atmosphere.h"

#ifndef M_PI
#define M_PI 3.14159
#endif

template<typename T>
void renderImage(const Vec3<T> sunDirection, QString filename, int rs, int ms)
{
    Atmosphere<T> atmosphere(sunDirection, rs, ms);
    const int width = 640, height = 480;
    Vec3<T> *image = new Vec3<T>[width * height], *p = image;
    memset(image, 0, sizeof(Vec3<T>) * width * height);
    T aspectRatio = width / T(height);
    T fieldOfView = 65;
    T angle = tan(fieldOfView * M_PI / 180. * 0.5);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j, ++p) {
            T ray_x = (2 * (j + (rand() / (RAND_MAX + 1.0))) / T(width) - 1) * aspectRatio * angle;
            T ray_y = (1 - (i + (rand() / (RAND_MAX + 1.0))) / T(height) * 2) * angle;
            Vec3<T> rayDirection(ray_x, ray_y, -1);
            rayDirection.normalize();
            Ray<T> ray(Vec3<T>(0, atmosphere.radiusEarth + 1000, 30000), rayDirection);
            T t0, t1;
            if (intersect<T>(ray, atmosphere.radiusEarth, t0, t1) && t1 > 0)
                ray.tmax = std::max(T(0), t0);
            *p += atmosphere.defineLight(ray);
        }
    }
    std::ofstream stream;
    QByteArray ba = filename.toLatin1();
    const char* filename_c = ba.data();
    stream.open(filename_c, std::ios::out | std::ios::binary );
    stream << "P6\n" << width << " " << height << "\n255\n";
    p = image;
    int dimensions = 3;
    for (int i = 0; i < height * width; ++i, ++p) {
        for (int j = 0; j < dimensions; ++j) {
            (*p)[j] = (*p)[j] < 1.41 ? pow((*p)[j] * 0.38, 1.0 / 2.2) : 1.0 - exp(-(*p)[j]);
            stream << (unsigned char)(std::min(T(1), (*p)[j]) * 255);
        }
    }
    stream.close();
    delete [] image;
}
