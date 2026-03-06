#pragma once

#include <cmath>

#include "ftm/vec.hpp"
#include "ftm/mat.hpp"
#include "ftm/utils.hpp"

namespace ftm {
class quat {
private:
	vec4	m_data;

public:
	quat();
	quat(float x, float y, float z, float w);
	quat(const quat& other);

	quat&			operator=(const quat& other);
	quat			operator*(const quat& other) const;
	vec3			operator*(const vec3& v) const;
	float&			operator[](std::size_t index);
	const float&	operator[](std::size_t index) const;
};

quat	angleAxis(float angle, const vec3& axis);
quat	normalize(const quat& q);
mat4	toMat4(const quat& q);
quat	rotate(const quat& q, float angle, const vec3& axis);
}
