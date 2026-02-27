#pragma once

#include "ComponentManager.hpp"

using namespace ecs;

template <typename ComponentType>
ComponentManager<ComponentType>::ComponentManager() : m_components(), m_entityToComponentIndex(), m_componentIndexToEntity(), m_componentCount(0) {
}

template <typename ComponentType>
void	ComponentManager<ComponentType>::addComponent(const Entity& entity, const ComponentType& component) {
	if (m_componentCount >= maxComponents) {
		throw std::runtime_error("Maximum number of components reached");
	}
	
	size_t	componentIndex = m_componentCount;
	m_components[componentIndex] = component;
	m_entityToComponentIndex[entity] = componentIndex;
	m_componentIndexToEntity[componentIndex] = entity;
	m_componentCount++;
}

template <typename ComponentType>
void	ComponentManager<ComponentType>::removeComponent(const Entity& entity) {
	auto it = m_entityToComponentIndex.find(entity);
	if (it == m_entityToComponentIndex.end()) {
		throw std::runtime_error("Entity does not have a component of this type");
	}

	size_t componentIndex = it->second;
	m_components[componentIndex] = m_components[m_componentCount - 1];
	m_entityToComponentIndex.erase(it);
	m_componentIndexToEntity[componentIndex] = m_componentIndexToEntity[m_componentCount - 1];
	m_componentCount--;
}

template <typename ComponentType>
ComponentManager<ComponentType>&	ComponentManager<ComponentType>::operator=(const ComponentManager& other) {
	if (this == &other)
		return *this;
	m_components = other.m_components;
	m_entityToComponentIndex = other.m_entityToComponentIndex;
	m_componentIndexToEntity = other.m_componentIndexToEntity;
	m_componentCount = other.m_componentCount;
	return *this;
}
