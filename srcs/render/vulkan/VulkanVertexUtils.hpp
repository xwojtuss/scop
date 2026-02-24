#pragma once

#include <vulkan/vulkan.h>

#include "../GpuTypes.hpp"

namespace render::vulkan {

VkVertexInputBindingDescription						getBindingDescription();
std::array<VkVertexInputAttributeDescription, 3>	getAttributeDescriptions();

}