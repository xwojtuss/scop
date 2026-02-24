#pragma once

#include <string>
#include <stdexcept>
#include <tiny_obj_loader.h>

#include "IModelLoader.hpp"
#include "Resources.hpp"
#include "../render/GpuTypes.hpp"

namespace assets {
class TinyObjLoader : public IModelLoader {
public:
	TinyObjLoader() = default;
	virtual ~TinyObjLoader();

	virtual MeshData	toMeshData(const char* path);
	virtual MeshData	toMeshData(std::string path);
};
}
