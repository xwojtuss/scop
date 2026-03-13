#include "BlockData.hpp"

using namespace game::block;

BlockDatas::BlockDatas() {
	m_blockDatas[0] = {
		"Air",
		assets::MeshData{},
		assets::TextureData{}
	};
	assets::MeshData cubeMeshData;
	cubeMeshData.vertices = {
		{{0.0f, 0.0f, 0.0f}, {0.1f, 1.0f, 1.0f}, {0.0f, 0.0f}},
		{{1.0f, 0.0f, 0.0f}, {1.0f, 0.1f, 1.0f}, {1.0f, 0.0f}},
		{{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.1f}, {1.0f, 1.0f}},
		{{0.0f, 1.0f, 0.0f}, {0.1f, 0.1f, 1.0f}, {0.0f, 1.0f}},
		{{1.0f, 1.0f, 1.0f}, {1.0f, 0.1f, 0.1f}, {1.0f, 1.0f}},
		{{0.0f, 1.0f, 1.0f}, {0.1f, 1.0f, 0.1f}, {0.0f, 1.0f}},
		{{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
		{{1.0f, 0.0f, 1.0f}, {0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
	};
	cubeMeshData.indices = {
		// Front face
		4, 5, 6,
		6, 7, 4,
		// Back face
		2, 1, 0,
		0, 3, 2,
		// Top face
		2, 3, 4,
		4, 3, 5,
		// Bottom face
		8, 7, 6,
		1, 7, 8,
		// Left face
		0, 6, 5,
		0, 5, 3,
		// Right face
		1, 2, 4,
		7, 1, 4
	};
	assets::TextureData cubeTextureData{};
	cubeTextureData.width = 16;
	cubeTextureData.height = 16;
	cubeTextureData.mipLevels = 1;
	uint8_t cubeTexturePixels[16 * 16 * 4] = {
		0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0xff, 0xff,
		0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0xff, 0xff,
		0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0xff, 0xff,
		0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0xff, 0xff,
	};
	cubeTextureData.pixels = cubeTexturePixels;
	cubeTextureData.freePixels = nullptr;
	m_blockDatas[1] = {
		"Dirt",
		cubeMeshData,
		cubeTextureData
	};
}

BlockData&	BlockDatas::getBlockData(BlockId id) {
	return m_blockDatas[id];
}
