#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include <cstdlib>
#include <cstring>

namespace render::vulkan {

typedef std::vector<const char*>	ValidationLayers;

class VulkanValidationLayers {
public:
	static const ValidationLayers	layers;
#ifdef NDEBUG
	static constexpr bool	isEnabled = false;
#else
	static constexpr bool	isEnabled = true;
#endif

	static bool	checkSupport();
};
}