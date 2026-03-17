#include "BlockData.hpp"

using namespace game::block;

BlockDatas::BlockDatas(assets::MeshData defaultMeshData, assets::TextureData defaultTextureData) : m_defaultMeshData(defaultMeshData), m_defaultTextureData(defaultTextureData) {
	m_blockDatas[0] = {
		"Air",
		assets::MeshData{},
		assets::TextureData{}
	};
	
	m_blockDatas[1] = {
		"Dirt",
		m_defaultMeshData,
		m_defaultTextureData
	};
}

BlockData&	BlockDatas::getBlockData(BlockId id) {
	return m_blockDatas[id];
}
