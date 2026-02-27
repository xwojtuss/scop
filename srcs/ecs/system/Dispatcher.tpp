#pragma once

#include "Dispatcher.hpp"

template<typename Event, typename SystemType>
void	Dispatcher::subscribe(SystemType* instance, void (SystemType::*method)(const Event&)) {
	auto& listeners = m_listeners[typeid(Event)];

	listeners.emplace_back([instance, method](const void* event) {
		(instance->*method)(*static_cast<const Event*>(event));
	}
	);
}

template<typename Event>
void	Dispatcher::emit(const Event& event) {
	auto it = m_listeners.find(typeid(Event));
	if (it == m_listeners.end())
		return;

	for (auto& listener : it->second)
		listener(&event);
}
