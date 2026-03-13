#pragma once

#include "Chunk.hpp"
#include "../../assets/Resources.hpp"

namespace game::world {
class ChunkMesher {
private:
public:
	ChunkMesher() = default;

	assets::MeshData	toMeshData(const Chunk& chunk);
};
}
