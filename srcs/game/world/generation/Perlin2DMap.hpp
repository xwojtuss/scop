#pragma once

#include <algorithm>
#include <glm/gtc/noise.hpp>

namespace game::world {
class Perlin2DMap {
private:
	float*			m_data;
	unsigned int	m_width;
	unsigned int	m_height;
	unsigned int	m_octaves;
	float			m_scale;

	void	generate();
	float	sampleValue(int x, int y) const;

	inline static float	perlinNoise(float x, float y);

public:
	Perlin2DMap(unsigned int width, unsigned int height, unsigned int octaves, float scale);
	~Perlin2DMap();

	float	getValue(int x, int y) const;
	float	getNormalizedValue(int x, int y) const;
	float	getValue(unsigned int x, unsigned int y) const;
};
}
