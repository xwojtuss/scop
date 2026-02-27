#pragma once

namespace ecs {
struct ComponentId {
	static int	id;
};

template <typename ComponentType>
struct Component {
	static int	getId();
};
}

#include "Component.tpp"
