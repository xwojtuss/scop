#include "Component.hpp"

using namespace ecs;

int	ComponentId::id = 1;

std::ostream&	operator<<(std::ostream& os, const IComponent& component) {
	return component.print(os);
}

const std::string&	IComponent::getName() const {
	return m_name;
}
