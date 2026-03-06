#pragma once

#include "ftm/ftm.hpp"

namespace render {
// One per frame
struct alignas(16) FrameUBO {
	ftm::mat4	view;
	ftm::mat4	proj;
};

/** One per draw/object
 * For now a push constant
 * using 64 bytes of the 128 available
 */
struct alignas(16) ObjectUBO {
	ftm::mat4	model;
};

struct alignas(16) TextUBO {
	ftm::vec2	position;
	ftm::vec2	size;
	ftm::vec4	color;
};

struct Vertex {
	ftm::vec3	pos;
	ftm::vec3	color;
	ftm::vec2	texCoord;

	bool	operator==(const Vertex& other) const {
		return pos == other.pos && color == other.color && texCoord == other.texCoord;
	}
};

struct Vertex2D {
	ftm::vec2	pos;
	ftm::vec3	color;
	ftm::vec2	texCoord;

	bool	operator==(const Vertex2D& other) const {
		return pos == other.pos && color == other.color && texCoord == other.texCoord;
	}
};

struct InstanceData {
	ftm::vec2	texCoord;
	int			charIndex;
};
}

namespace std {
	template<> struct hash<render::Vertex> {
		size_t operator()(render::Vertex const& vertex) const {
			return ((hash<ftm::vec3>()(vertex.pos) ^
				(hash<ftm::vec3>()(vertex.color) << 1)) >> 1) ^
				(hash<ftm::vec2>()(vertex.texCoord) << 1);
		}
	};
}
