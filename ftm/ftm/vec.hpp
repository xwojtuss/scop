#pragma once

#include <cstddef>
#include <functional>

namespace ftm {
template <typename T, std::size_t N>
class vec {
private:
	T	m_data[N];

public:
	constexpr vec();
	constexpr vec(const T& value);
	constexpr vec(const vec& other);
	
	template <typename... Args>
	constexpr vec(Args... args);
	
	vec&					operator=(const vec& other);
	constexpr T&			operator[](std::size_t index);
	constexpr const T&		operator[](std::size_t index) const;
	constexpr vec			operator+(const vec& other) const;
	constexpr vec			operator-(const vec& other) const;
	constexpr vec			operator*(const T& scalar) const;
	constexpr vec			operator*(const vec& other) const;
	constexpr vec			operator/(const T& scalar) const;
	constexpr vec			operator/(const vec& other) const;
	vec&					operator+=(const vec& other);
	vec&					operator-=(const vec& other);
	vec&					operator*=(const T& scalar);
	vec&					operator/=(const T& scalar);
	bool					operator==(const vec& other) const;
	constexpr vec			operator-() const;
};
typedef vec<float, 2>	vec2;
typedef vec<float, 3>	vec3;
typedef vec<float, 4>	vec4;

template <typename T, std::size_t N>
T	dot(const vec<T, N>& a, const vec<T, N>& b);

vec3	cross(const vec3& a, const vec3& b);
}

namespace std {
	template<typename T, std::size_t N>
	struct hash<ftm::vec<T, N>> {
		size_t operator()(const ftm::vec<T, N>& vec) const {
			size_t result = 0;
			for (std::size_t i = 0; i < N; ++i) {
				result ^= hash<T>()(vec[i]) + 0x9e3779b9 + (result << 6) + (result >> 2);
			}
			return result;
		}
	};
}

#include "../srcs/vec/vec.tpp"
