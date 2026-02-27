#pragma once

#include <unordered_map>
#include <vector>
#include <typeindex>
#include <functional>

namespace ecs {
typedef std::function<void(const void*)>	Listener;
class Dispatcher {
private:
	std::unordered_map<std::type_index, std::vector<Listener>>	m_listeners;

public:
	template<typename Event, typename SystemType>
	void subscribe(SystemType* instance, void (SystemType::*method)(const Event&));

	template<typename Event>
	void emit(const Event& event);
};
}

#include "Dispatcher.tpp"
