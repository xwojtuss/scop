#pragma once

#include "Component.hpp"

using namespace ecs;

template <typename ComponentType>
int	Component<ComponentType>::getId() {
	static int id = ComponentId::id++;
	return id;
}

template <typename ComponentType>
std::ostream&	Component<ComponentType>::print(std::ostream& os) const {
	return os << "Component";
}
