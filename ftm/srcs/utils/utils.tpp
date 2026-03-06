#pragma once

#include <cmath>

#include "ftm/utils.hpp"

namespace ftm {
template <typename T>
T	clamp(const T& value, const T& min, const T& max) {
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

template <typename T>
T	abs(const T& value) {
	return (value < T(0)) ? -value : value;
}

template <typename T>
T	max(const T& a, const T& b) {
	return (a > b) ? a : b;
}

template <typename T>
T	min(const T& a, const T& b) {
	return (a < b) ? a : b;
}

template <typename T, std::size_t N>
vec<T, N>	min(const vec<T, N>& a, const vec<T, N>& b) {
	vec<T, N> result;
	for (std::size_t i = 0; i < N; ++i) {
		result[i] = (a[i] < b[i]) ? a[i] : b[i];
	}
	return result;
}

template <typename T, std::size_t N>
vec<T, N>	max(const vec<T, N>& a, const vec<T, N>& b) {
	vec<T, N> result;
	for (std::size_t i = 0; i < N; ++i) {
		result[i] = (a[i] > b[i]) ? a[i] : b[i];
	}
	return result;
}

template <typename T>
float	length(const T& value) {
	return std::sqrt(dot(value, value));
}

template <typename T>
T	scale(const T& value, float factor) {
	return value * factor;
}

template <typename T>
T	normalize(const T& value) {
	float len = length(value);

	if (len > 0) {
		return value / len;
	}
	return value;
}
}
