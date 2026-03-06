#include "ftm/quat.hpp"

using namespace ftm;

quat::quat() : m_data(0.0f, 0.0f, 0.0f, 1.0f) {
}

quat::quat(float x, float y, float z, float w) : m_data(x, y, z, w) {
}

quat::quat(const quat& other) : m_data(other.m_data) {
}

quat&	quat::operator=(const quat& other) {
	m_data = other.m_data;
	return *this;
}

quat	quat::operator*(const quat& other) const {
	quat result;

	result.m_data[0] = m_data[3] * other.m_data[0] + m_data[0] * other.m_data[3] + m_data[1] * other.m_data[2] - m_data[2] * other.m_data[1];
	result.m_data[1] = m_data[3] * other.m_data[1] - m_data[0] * other.m_data[2] + m_data[1] * other.m_data[3] + m_data[2] * other.m_data[0];
	result.m_data[2] = m_data[3] * other.m_data[2] + m_data[0] * other.m_data[1] - m_data[1] * other.m_data[0] + m_data[2] * other.m_data[3];
	result.m_data[3] = m_data[3] * other.m_data[3] - m_data[0] * other.m_data[0] - m_data[1] * other.m_data[1] - m_data[2] * other.m_data[2];

	return result;
}

float&	quat::operator[](std::size_t index) {
	return m_data[index];
}

const float&	quat::operator[](std::size_t index) const {
	return m_data[index];
}

vec3	quat::operator*(const vec3& v) const {
	vec3 qxyz(m_data[0], m_data[1], m_data[2]);
	float w = m_data[3];
	
	vec3 t = cross(qxyz, v) * 2.0f;
	return v + t * w + cross(qxyz, t);
}

quat	ftm::angleAxis(float angle, const vec3& axis) {
	float halfAngle = angle / 2.0f;
	float s = std::sin(halfAngle);

	return quat(axis[0] * s, axis[1] * s, axis[2] * s, std::cos(halfAngle));
}

quat	ftm::normalize(const quat& q) {
	float len = std::sqrt(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);

	return (len > 0) ? quat(q[0] / len, q[1] / len, q[2] / len, q[3] / len) : quat(0.0f, 0.0f, 0.0f, 1.0f);
}

mat4	ftm::toMat4(const quat& q) {
	mat4 result(1.0f);

	float x = q[0], y = q[1], z = q[2], w = q[3];

	float x2 = x + x, y2 = y + y, z2 = z + z;
	float xx = x * x2, xy = x * y2, xz = x * z2;
	float yy = y * y2, yz = y * z2, zz = z * z2;
	float wx = w * x2, wy = w * y2, wz = w * z2;

	result[0][0] = 1 - (yy + zz);
	result[0][1] = xy + wz;
	result[0][2] = xz - wy;
	result[1][0] = xy - wz;
	result[1][1] = 1 - (xx + zz);
	result[1][2] = yz + wx;
	result[2][0] = xz + wy;
	result[2][1] = yz - wx;
	result[2][2] = 1 - (xx + yy);

	return result;
}

quat	ftm::rotate(const quat& q, float angle, const vec3& axis) {
	quat rotation = angleAxis(angle, axis);

	return q * rotation;
}
