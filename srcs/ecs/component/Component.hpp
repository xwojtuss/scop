#pragma once

namespace ecs {
struct ComponentId {
	static int	id;
};

template <typename ComponentType>
struct Component {
	static int	getId();
};

struct Message : public Component<Message> {
	char	message[256];
};

struct Number : public Component<Number> {
	int	value;
};
}

#include "Component.tpp"
