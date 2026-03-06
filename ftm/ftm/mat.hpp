#pragma once

#include <cstddef>
#include <cmath>

#include "ftm/vec.hpp"

namespace ftm {
template <typename T, std::size_t N>
class mat {
private:
	T	m_data[N][N];

public:
	mat();
	mat(const T& value);
	mat(const mat& other);
	template <typename... Args>
	mat(Args... args);

	mat			operator*(const mat& other) const;
	mat&		operator=(const mat& other);
	T*			operator[](std::size_t index);
	const T*	operator[](std::size_t index) const;
};
typedef mat<float, 2>	mat2;
typedef mat<float, 3>	mat3;
typedef mat<float, 4>	mat4;

mat4	translate(const mat4& matrix, const vec3& translation);
mat4	scale(const mat4& matrix, const vec3& s);
mat4	lookAt(const vec3& eye, const vec3& center, const vec3& up);
mat4	perspective(float fov, float aspect, float near, float far);
}

#include "../srcs/mat/mat.tpp"
