#include "EntityManager.hpp"

using namespace ecs;

EntityManager::EntityManager() : lastEntity(1) {
}

Entity	EntityManager::createEntity() {
	return lastEntity++;
}
