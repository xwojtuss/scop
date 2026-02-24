#pragma once

#include "../scene/Scene.hpp"
#include "../assets/Resources.hpp"

namespace render {

class IRenderer {
public:
	virtual ~IRenderer() = default;

	virtual assets::MeshHandle		createMesh(const assets::MeshData&) = 0;
	virtual assets::TextureHandle	createTexture(const assets::TextureData&) = 0;
	virtual void					beginFrame() = 0;
	virtual void					render(scene::Scene&) = 0;
	virtual void					endFrame() = 0;
	virtual void					setClearColor(float r, float g, float b, float a) = 0;
	virtual void					cleanup() = 0;
};
}