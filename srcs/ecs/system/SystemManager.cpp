#include "SystemManager.hpp"

using namespace ecs;

void	SystemManager::onRender(float aspectRatio, double time) {
	m_dispatcher.emit<RenderEvent>(RenderEvent{aspectRatio, time});
}

void	SystemManager::onTextDraw(render::IRenderer& renderer) {
	m_dispatcher.emit<TextDrawEvent>(TextDrawEvent{&renderer});
}

void	SystemManager::onRendererDraw(render::IRenderer& renderer) {
	m_dispatcher.emit<RendererDrawEvent>(RendererDrawEvent{&renderer});
}

void	SystemManager::onRendererFrame(render::IRenderer& renderer) {
	m_dispatcher.emit<RendererFrameEvent>(RendererFrameEvent{&renderer});
}

void	SystemManager::onSimulate(float deltaTime) {
	m_dispatcher.emit<SimulateEvent>(SimulateEvent{deltaTime});
}

Dispatcher&	SystemManager::getDispatcher() {
	return m_dispatcher;
}
