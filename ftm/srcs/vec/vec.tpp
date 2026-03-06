#pragma once

#include "ftm/vec.hpp"

namespace ftm {
template <typename T, std::size_t N>
constexpr vec<T, N>::vec() : m_data{} {
}

template <typename T, std::size_t N>
constexpr vec<T, N>::vec(const T& value) : m_data{} {
	for (std::size_t i = 0; i < N; ++i) {
		m_data[i] = value;
	}
}

template <typename T, std::size_t N>
constexpr vec<T, N>::vec(const vec& other) : m_data{} {
	for (std::size_t i = 0; i < N; ++i) {
		m_data[i] = other.m_data[i];
	}
}

template <typename T, std::size_t N>
template <typename... Args>
constexpr vec<T, N>::vec(Args... args) : m_data{static_cast<T>(args)...} {
	static_assert(sizeof...(args) == N, "Number of arguments must match vector size");
}

template <typename T, std::size_t N>
vec<T, N>&	vec<T, N>::operator=(const vec& other) {
	for (std::size_t i = 0; i < N; ++i) {
		m_data[i] = other.m_data[i];
	}
	return *this;
}

template <typename T, std::size_t N>
constexpr T&	vec<T, N>::operator[](std::size_t index) {
	return m_data[index];
}

template <typename T, std::size_t N>
constexpr const T&	vec<T, N>::operator[](std::size_t index) const {
	return m_data[index];
}

template <typename T, std::size_t N>
constexpr vec<T, N>	vec<T, N>::operator+(const vec& other) const {
	vec<T, N> result;
	for (std::size_t i = 0; i < N; ++i) {
		result.m_data[i] = m_data[i] + other.m_data[i];
	}
	return result;
}

template <typename T, std::size_t N>
constexpr vec<T, N>	vec<T, N>::operator-(const vec& other) const {
	vec<T, N> result;
	for (std::size_t i = 0; i < N; ++i) {
		result.m_data[i] = m_data[i] - other.m_data[i];
	}
	return result;
}

template <typename T, std::size_t N>
constexpr vec<T, N>	vec<T, N>::operator*(const T& scalar) const {
	vec<T, N> result;
	for (std::size_t i = 0; i < N; ++i) {
		result.m_data[i] = m_data[i] * scalar;
	}
	return result;
}

template <typename T, std::size_t N>
constexpr vec<T, N>	vec<T, N>::operator*(const vec& other) const {
	vec<T, N> result;
	for (std::size_t i = 0; i < N; ++i) {
		result.m_data[i] = m_data[i] * other.m_data[i];
	}
	return result;
}


template <typename T, std::size_t N>
constexpr vec<T, N>	vec<T, N>::operator/(const T& scalar) const {
	vec<T, N> result;
	for (std::size_t i = 0; i < N; ++i) {
		result.m_data[i] = m_data[i] / scalar;
	}
	return result;
}

template <typename T, std::size_t N>
constexpr vec<T, N>	vec<T, N>::operator/(const vec& other) const {
	vec<T, N> result;
	for (std::size_t i = 0; i < N; ++i) {
		result.m_data[i] = m_data[i] / other.m_data[i];
	}
	return result;
}

template <typename T, std::size_t N>
vec<T, N>&	vec<T, N>::operator+=(const vec& other) {
	for (std::size_t i = 0; i < N; ++i) {
		m_data[i] += other.m_data[i];
	}
	return *this;
}

template <typename T, std::size_t N>
vec<T, N>&	vec<T, N>::operator-=(const vec& other) {
	for (std::size_t i = 0; i < N; ++i) {
		m_data[i] -= other.m_data[i];
	}
	return *this;
}

template <typename T, std::size_t N>
vec<T, N>&	vec<T, N>::operator*=(const T& scalar) {
	for (std::size_t i = 0; i < N; ++i) {
		m_data[i] *= scalar;
	}
	return *this;
}

template <typename T, std::size_t N>
vec<T, N>&	vec<T, N>::operator/=(const T& scalar) {
	for (std::size_t i = 0; i < N; ++i) {
		m_data[i] /= scalar;
	}
	return *this;
}

template <typename T, std::size_t N>
bool	vec<T, N>::operator==(const vec& other) const {
	for (std::size_t i = 0; i < N; ++i) {
		if (m_data[i] != other.m_data[i]) {
			return false;
		}
	}
	return true;
}

template <typename T, std::size_t N>
constexpr vec<T, N>	vec<T, N>::operator-() const {
	vec<T, N> result;

	for (std::size_t i = 0; i < N; ++i) {
		result.m_data[i] = -m_data[i];
	}
	return result;
}

template <typename T, std::size_t N>
T	dot(const vec<T, N>& a, const vec<T, N>& b) {
	T result = T(0);
	for (std::size_t i = 0; i < N; ++i) {
		result += a[i] * b[i];
	}
	return result;
}
}
