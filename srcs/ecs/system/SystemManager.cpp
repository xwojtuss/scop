#include "SystemManager.hpp"

using namespace ecs;

void	SystemManager::onRender(float aspectRatio) {
	m_dispatcher.emit<RenderEvent>(RenderEvent{aspectRatio});
}

void	SystemManager::onRendererDraw(render::IRenderer& renderer) {
	m_dispatcher.emit<RendererDrawEvent>(RendererDrawEvent{&renderer});
}

void	SystemManager::onRendererFrame(render::IRenderer& renderer) {
	m_dispatcher.emit<RendererFrameEvent>(RendererFrameEvent{&renderer});
}

Dispatcher&	SystemManager::getDispatcher() {
	return m_dispatcher;
}
