#pragma once

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
	game::Block*	m_blocks;
	glm::ivec3		m_chunkPosition;

public:
	Chunk(int x = 0, int y = 0, int z = 0);
	Chunk(glm::ivec3 chunkPosition);
	~Chunk();

	game::Block&		getBlock(unsigned short x, unsigned short y, unsigned short z);
	const game::Block&	getBlock(unsigned short x, unsigned short y, unsigned short z) const;
	glm::ivec3			getBlockPosition(unsigned short x, unsigned short y, unsigned short z) const;
	glm::ivec3			getChunkPosition() const;
	void				setChunkPosition(int x, int y, int z);
	void				setChunkPosition(glm::ivec3 chunkPosition);
	void				setBlock(unsigned short x, unsigned short y, unsigned short z, const game::Block& block);
	void				removeBlock(unsigned short x, unsigned short y, unsigned short z);
};
}
