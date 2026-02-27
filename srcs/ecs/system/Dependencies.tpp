#pragma once

#include "Dependencies.hpp"

using namespace ecs;

template <typename ComponentType>
void	Dependencies::addDependency() {
	mask.set(ComponentType::getId());
}

template <typename ComponentType>
void	Dependencies::removeDependency() {
	mask.reset(ComponentType::getId());
}

template <typename ComponentType>
bool	Dependencies::includes() const {
	return mask.test(ComponentType::getId());
}
