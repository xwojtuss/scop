#pragma once

#include <string>
#include <stdexcept>

#include "Resources.hpp"

namespace assets {
class ITextureLoader {
public:
	virtual ~ITextureLoader() = default;

	virtual TextureData	toTextureData(const char* path) = 0;
	virtual TextureData	toTextureData(std::string path) = 0;
};
}