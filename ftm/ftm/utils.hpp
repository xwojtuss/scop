#pragma once

#include "vec.hpp"

#define FTM_PI 3.14159265358979323846f

namespace ftm {
float	radians(float degrees);

template <typename T>
T	clamp(const T& value, const T& min, const T& max);

template <typename T>
T	abs(const T& value);

template <typename T>
T	max(const T& a, const T& b);

template <typename T>
T	min(const T& a, const T& b);

template <typename T, std::size_t N>
vec<T, N>	min(const vec<T, N>& a, const vec<T, N>& b);

template <typename T, std::size_t N>
vec<T, N>	max(const vec<T, N>& a, const vec<T, N>& b);

template <typename T>
float	length(const T& value);

template <typename T>
T	scale(const T& value, float factor);

template <typename T>
T	normalize(const T& value);
}

#include "../srcs/utils/utils.tpp"
