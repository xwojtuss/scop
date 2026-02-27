#pragma once

#include <unordered_map>
#include <memory>
#include <typeindex>

#include "ASystem.hpp"
#include "Dispatcher.hpp"
#include "DispatcherEvents.hpp"

namespace ecs {
class SystemManager {
private:
	std::unordered_map<std::type_index, std::unique_ptr<ASystem>>	m_systems;
	Dispatcher														m_dispatcher;

public:
	template <typename SystemType>
	SystemType&	addSystem();
	
	template <typename SystemType>
	SystemType*	getSystem();
	
	void		onTick();
	Dispatcher&	getDispatcher();
};
}

#include "SystemManager.tpp"
