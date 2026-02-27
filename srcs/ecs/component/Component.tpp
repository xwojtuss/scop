#pragma once

#include "Component.hpp"

using namespace ecs;

template <typename ComponentType>
int	Component<ComponentType>::getId() {
	static int id = ComponentId::id++;
	return id;
}