#include "Perlin2DMap.hpp"

using namespace game::world;

Perlin2DMap::Perlin2DMap(unsigned int width, unsigned int height, unsigned int octaves, float scale) : m_width(width), m_height(height), m_octaves(octaves), m_scale(scale) {
	m_data = new float[width * height];
	generate();
}

Perlin2DMap::~Perlin2DMap() {
	delete[] m_data;
}

float	Perlin2DMap::sampleValue(int x, int y) const {
	float amplitude = 1.0f;
	float frequency = 1.0f;
	float noiseValue = 0.0f;

	for (unsigned int octave = 0; octave < m_octaves; ++octave) {
		noiseValue += amplitude * perlinNoise(static_cast<float>(x) * frequency * m_scale, static_cast<float>(y) * frequency * m_scale);
		amplitude *= 0.5f;
		frequency *= 2.0f;
	}

	return noiseValue;
}

float	Perlin2DMap::getValue(int x, int y) const {
	if (x >= 0 && y >= 0 && static_cast<unsigned int>(x) < m_width && static_cast<unsigned int>(y) < m_height) {
		return m_data[static_cast<unsigned int>(x) + m_width * static_cast<unsigned int>(y)];
	}
	return sampleValue(x, y);
}

float	Perlin2DMap::getNormalizedValue(int x, int y) const {
	return std::clamp((getValue(x, y) + 1.0f) * 0.5f, 0.0f, 1.0f);
}

inline float	Perlin2DMap::perlinNoise(float x, float y) {
	return glm::perlin(glm::vec2(x, y));
}

void	Perlin2DMap::generate() {
	for (unsigned int x = 0; x < m_width; ++x) {
		for (unsigned int y = 0; y < m_height; ++y) {
			m_data[x + m_width * y] = sampleValue(static_cast<int>(x), static_cast<int>(y));
		}
	}
}
