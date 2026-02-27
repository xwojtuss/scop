#pragma once

#include <bitset>

namespace ecs {
typedef std::bitset<32>	DependencyMask;

struct Dependencies {
	DependencyMask	mask;

	Dependencies();

	template <typename ComponentType>
	void		addDependency();

	template <typename ComponentType>
	void		removeDependency();

	template <typename ComponentType>
	bool		includes() const;

	bool		matches(const Dependencies& other) const;
};
}

#include "Dependencies.tpp"
