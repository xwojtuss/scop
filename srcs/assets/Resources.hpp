#pragma once

#include <cstdint>
#include <vector>
#include <cstddef>
#include <functional>

#include "../render/GpuTypes.hpp"

namespace assets {
struct MeshData {
	std::vector<render::Vertex>	vertices;
	std::vector<uint32_t>		indices;
};

struct TextureData {
	uint32_t	width;
	uint32_t	height;
	uint32_t	mipLevels;
	void*		pixels;
	std::function<void(void*)>	freePixels;
};

struct MeshHandle {
	static uint64_t	nextId;
	uint64_t		id;

	MeshHandle() : id(nextId++) {}
};

struct TextureHandle {
	static uint64_t	nextId;
	uint64_t		id;

	TextureHandle() : id(nextId++) {}
};

}
