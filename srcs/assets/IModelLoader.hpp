#pragma once

#include <string>

#include "Resources.hpp"

namespace assets {
class IModelLoader {
public:
	virtual ~IModelLoader() = default;

	virtual MeshData	toMeshData(const char* path) = 0;
	virtual MeshData	toMeshData(std::string path) = 0;
};
}
