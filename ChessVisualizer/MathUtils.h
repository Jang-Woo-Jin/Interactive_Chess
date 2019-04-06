#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <cmath>
#include <random>
#include <ctime>

constexpr double PI = 3.141592;

constexpr double degreeToRadian(double degree)
{
    return degree * (PI / 180.0);
}

template <typename T>
T pickRandomNumber(T minInclusive, T maxExclusive)
{
    using TDistribution = std::uniform_int_distribution<T>;

    static thread_local std::default_random_engine engine{ static_cast<unsigned int>(time(nullptr)) };
    static TDistribution distribution;

    return distribution(engine, TDistribution::param_type(minInclusive, maxExclusive - 1));
}

#endif // MATHUTILS_H
