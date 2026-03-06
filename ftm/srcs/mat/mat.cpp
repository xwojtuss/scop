#include "ftm/mat.hpp"
#include "ftm/utils.hpp"

namespace ftm {

mat4	translate(const mat4& matrix, const vec3& translation) {
	mat4 result = matrix;

	vec4 t(matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3]);

	result[3][0] = matrix[0][0] * translation[0] + matrix[1][0] * translation[1] + matrix[2][0] * translation[2] + t[0];
	result[3][1] = matrix[0][1] * translation[0] + matrix[1][1] * translation[1] + matrix[2][1] * translation[2] + t[1];
	result[3][2] = matrix[0][2] * translation[0] + matrix[1][2] * translation[1] + matrix[2][2] * translation[2] + t[2];
	result[3][3] = matrix[0][3] * translation[0] + matrix[1][3] * translation[1] + matrix[2][3] * translation[2] + t[3];

	return result;
}

mat4	scale(const mat4& matrix, const vec3& s) {
	mat4 result = matrix;

	result[0][0] *= s[0];
	result[0][1] *= s[0];
	result[0][2] *= s[0];
	result[0][3] *= s[0];
	
	result[1][0] *= s[1];
	result[1][1] *= s[1];
	result[1][2] *= s[1];
	result[1][3] *= s[1];
	
	result[2][0] *= s[2];
	result[2][1] *= s[2];
	result[2][2] *= s[2];
	result[2][3] *= s[2];

	return result;
}

mat4	lookAt(const vec3& eye, const vec3& center, const vec3& up) {
	vec3 forward = normalize(center - eye);
	vec3 right = normalize(cross(forward, up));
	vec3 upVec = cross(right, forward);

	mat4 result(1.0f);
	result[0][0] = right[0];
	result[0][1] = upVec[0];
	result[0][2] = -forward[0];
	result[1][0] = right[1];
	result[1][1] = upVec[1];
	result[1][2] = -forward[1];
	result[2][0] = right[2];
	result[2][1] = upVec[2];
	result[2][2] = -forward[2];
	result[3][0] = -dot(right, eye);
	result[3][1] = -dot(upVec, eye);
	result[3][2] = dot(forward, eye);

	return result;
}

mat4	perspective(float fov, float aspect, float near, float far)
{
	float screen = std::tan(fov * 0.5f);

	mat4 result(0.0f);

	result[0][0] = 1.0f / (aspect * screen);
	result[1][1] = 1.0f / screen;
	result[2][2] = far / (near - far);
	result[2][3] = -1.0f;
	result[3][2] = (far * near) / (near - far);

	return result;
}
}
