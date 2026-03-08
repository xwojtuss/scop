#pragma once

#include <ostream>
#include <string>

namespace ecs {
struct ComponentId {
	static int	id;
};

struct IComponent {
protected:
	std::string	m_name;

	IComponent(const std::string& name) : m_name(name) {}

public:
	virtual ~IComponent() = default;

	virtual std::ostream&		print(std::ostream& os) const = 0;
	const std::string&			getName() const;
};

template <typename ComponentType>
struct Component : public IComponent {
protected:
	Component(const std::string& name) : IComponent(name) {}

public:
	static int	getId();

	virtual std::ostream&	print(std::ostream& os) const override;
};
}
std::ostream&	operator<<(std::ostream& os, const ecs::IComponent& component);

#include "Component.tpp"
