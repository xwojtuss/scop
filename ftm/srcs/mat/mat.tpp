#pragma once

#include "ftm/mat.hpp"

namespace ftm {
template <typename T, std::size_t N>
mat<T, N>::mat() {
	for (std::size_t i = 0; i < N; ++i) {
		for (std::size_t j = 0; j < N; ++j) {
			m_data[i][j] = T(0);
		}
	}
}

template <typename T, std::size_t N>
mat<T, N>::mat(const T& value) {
	for (std::size_t i = 0; i < N; ++i) {
		for (std::size_t j = 0; j < N; ++j) {
			m_data[i][j] = (i == j) ? value : T(0);
		}
	}
}

template <typename T, std::size_t N>
mat<T, N>::mat(const mat& other) {
	for (std::size_t i = 0; i < N; ++i) {
		for (std::size_t j = 0; j < N; ++j) {
			m_data[i][j] = other.m_data[i][j];
		}
	}
}

template <typename T, std::size_t N>
template <typename... Args>
mat<T, N>::mat(Args... args) {
	static_assert(sizeof...(args) == N * N, "Number of arguments must match matrix size");
	T values[] = { static_cast<T>(args)... };

	for (std::size_t i = 0; i < N; ++i) {
		for (std::size_t j = 0; j < N; ++j) {
			m_data[i][j] = values[j * N + i];
		}
	}
}

template <typename T, std::size_t N>
mat<T, N>	mat<T, N>::operator*(const mat& other) const {
	mat<T, N> result;

	for (std::size_t i = 0; i < N; ++i) {
		for (std::size_t j = 0; j < N; ++j) {
			result.m_data[i][j] = T(0);

			for (std::size_t k = 0; k < N; ++k) {
				result.m_data[i][j] += m_data[k][j] * other.m_data[i][k];
			}
		}
	}
	return result;
}

template <typename T, std::size_t N>
mat<T, N>&	mat<T, N>::operator=(const mat& other) {
	for (std::size_t i = 0; i < N; ++i) {
		for (std::size_t j = 0; j < N; ++j) {
			m_data[i][j] = other.m_data[i][j];
		}
	}
	return *this;
}

template <typename T, std::size_t N>
T*	mat<T, N>::operator[](std::size_t index) {
	return m_data[index];
}

template <typename T, std::size_t N>
const T*	mat<T, N>::operator[](std::size_t index) const {
	return m_data[index];
}
}
