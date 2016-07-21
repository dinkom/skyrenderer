#include <cmath>
#include <cassert>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <QString>
#include "raytracer.h"
#include "helpers.cpp"

#ifndef M_PI
#define M_PI 3.14159
#endif

template<typename T>
class Atmosphere
{
public:
    Atmosphere(Vec3<T> sd = Vec3<T>(0, 1, 0), T rsh = 10000, T msh = 2000, T re = 6360e3, T ra = 6420e3) :
        rayleighScaleHeight(rsh), mieScaleHeight(msh), radiusEarth(re), radiusAtmosphere(ra), sunDirection(sd)
    {}
    static const Vec3<T> betaRayleigh;
    static const Vec3<T> betaMie;
    T rayleighScaleHeight;
    T mieScaleHeight;
    T radiusEarth;
    T radiusAtmosphere;
    Vec3<T> sunDirection;
    Vec3<T> defineLight(Ray<T> &r) const;
};

template<typename T>
const Vec3<T> Atmosphere<T>::betaRayleigh(3.8e-6, 13.5e-6, 33.1e-6);
template<typename T>
const Vec3<T> Atmosphere<T>::betaMie(21e-6);

template<typename T>
Vec3<T> Atmosphere<T>::defineLight(Ray<T> &r) const
{
    T t0, t1;
    if (!intersect<T>(r, radiusAtmosphere, t0, t1) || t1 < 0) return Vec3<T>(0);
    if (t0 > r.tmin && t0 > 0) r.tmin = t0;
    if (t1 < r.tmax) r.tmax = t1;
    int numSamples = 16;
    int numSamplesLight = 8;
    T segmentLength = (r.tmax - r.tmin) / numSamples;
    T tCurrent = r.tmin;
    Vec3<T> sumRayleigh(0), sumMie(0);
    T opticalDepthRayleigh = 0, opticalDepthMie = 0;
    T mi = r.direction.dot(sunDirection);
    T phaseRayleigh = 3 / (16 * M_PI) * (1 + mi * mi);
    T anisotropy = 0.76;
    T phaseMie = 3 / (8 * M_PI) * ((1 - anisotropy * anisotropy) * (1 + mi * mi))/((2 + anisotropy * anisotropy) * pow(1 + anisotropy * anisotropy - 2 * anisotropy * mi, 1.5));
    for (int i = 0; i < numSamples; ++i) {
        Vec3<T> samplePosition = r(tCurrent + T(0.5) * segmentLength);
        T height = samplePosition.length() - radiusEarth;
        T hr = exp(-height / rayleighScaleHeight) * segmentLength;
        T hm = exp(-height / mieScaleHeight) * segmentLength;
        opticalDepthRayleigh += hr;
        opticalDepthMie += hm;
        Ray<T> lightRay(samplePosition, sunDirection);
        intersect(lightRay, radiusAtmosphere, lightRay.tmin, lightRay.tmax);
        T segmentLengthLight = lightRay.tmax / numSamplesLight, tCurrentLight = 0;
        T opticalDepthLightRayleigh = 0, opticalDepthLightMie = 0;
        bool heightLightOk = true;
        for (int j = 0; j < numSamplesLight; ++j) {
            Vec3<T> samplePositionLight = lightRay(tCurrentLight + T(0.5) * segmentLengthLight);
            T heightLight = samplePositionLight.length() - radiusEarth;
            if (heightLight < 0) {
                heightLightOk = false;
                break;
            }
            opticalDepthLightRayleigh += exp(-heightLight / rayleighScaleHeight) * segmentLengthLight;
            opticalDepthLightMie += exp(-heightLight / mieScaleHeight) * segmentLengthLight;
            tCurrentLight += segmentLengthLight;
        }
        if (heightLightOk) {
            Vec3<T> tau = betaRayleigh * (opticalDepthRayleigh + opticalDepthLightRayleigh) + betaMie * 1.1 * (opticalDepthMie + opticalDepthLightMie);
            Vec3<T> attenuation(exp(-tau.x), exp(-tau.y), exp(-tau.z));
            sumRayleigh += attenuation * hr;
            sumMie += attenuation * hm;
        }
        tCurrent += segmentLength;
    }
    return (sumRayleigh * betaRayleigh * phaseRayleigh + sumMie * betaMie * phaseMie) * 30;
}
