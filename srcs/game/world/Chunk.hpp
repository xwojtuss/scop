#pragma once

#include <array>
#include <cstring>
#include <glm/vec3.hpp>

#include "../block/Block.hpp"

namespace game::world {

constexpr unsigned short	chunkXSize = 16;
constexpr unsigned short	chunkYSize = 16;
constexpr unsigned short	chunkZSize = 16;

/**
 * Holds blocks in a three dimensional C style array
 * @todo TODO: test if std::array will be better or maybe just using new or sth
 */
class Chunk {
private:
	std::array<game::Block, chunkXSize * chunkYSize * chunkZSize>	m_blocks;

public:
	Chunk() = default;
	~Chunk() = default;

	game::Block&		getBlock(unsigned short x, unsigned short y, unsigned short z);
	const game::Block&	getBlock(unsigned short x, unsigned short y, unsigned short z) const;
	glm::ivec3			getBlockPosition(unsigned short x, unsigned short y, unsigned short z) const;
	void				setBlock(unsigned short x, unsigned short y, unsigned short z, const game::Block& block);
	void				removeBlock(unsigned short x, unsigned short y, unsigned short z);
};
}
