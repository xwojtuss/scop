#include "SystemManager.hpp"

using namespace ecs;

void	SystemManager::onTick() {
	m_dispatcher.emit<TickEvent>(TickEvent());
}

Dispatcher&	SystemManager::getDispatcher() {
	return m_dispatcher;
}
