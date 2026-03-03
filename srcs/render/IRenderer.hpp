#pragma once

#include "../assets/Resources.hpp"
#include "../ecs/component/Components.hpp"
#include "../ecs/system/SystemManager.hpp"

namespace ecs {
class SystemManager;
}

namespace render {

class IRenderer {
public:
	virtual ~IRenderer() = default;

	virtual assets::MeshHandle			createMesh(const assets::MeshData&) = 0;
	virtual assets::TextureHandle		createTexture(const assets::TextureData&) = 0;
	virtual const assets::MeshHandle&	getTextMeshHandle() const = 0;
	virtual void						beginFrame() = 0;
	virtual void						render(ecs::SystemManager& systemManager) = 0;
	virtual void						endFrame() = 0;
	virtual void						setClearColor(float r, float g, float b, float a) = 0;
	virtual void						cleanup() = 0;
	virtual void						drawMesh(const ecs::component::Mesh& mesh, const ecs::component::Transform& transform) = 0;
	virtual void						drawText(const ecs::component::Text& text, const ecs::component::Transform2D& transform, size_t offset, const ecs::component::Color* color = nullptr) = 0;
	virtual void						updateCamera(const component::Camera& camera) = 0;
};
}