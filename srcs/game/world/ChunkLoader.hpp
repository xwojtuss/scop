#pragma once

namespace game::world {
class ChunkLoader {
private:
public:
	ChunkLoader() = default;
	~ChunkLoader() = default;

	void	loadChunk(unsigned short x, unsigned short y, unsigned short z);
	void	saveChunk(unsigned short x, unsigned short y, unsigned short z);
};
}
