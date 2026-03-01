#pragma once

#include <vulkan/vulkan.h>

#include "../GpuTypes.hpp"

namespace render::vulkan {

VkVertexInputBindingDescription						getBindingDescription();
VkVertexInputBindingDescription						getInstanceBindingDescription();
std::array<VkVertexInputAttributeDescription, 3>	getAttributeDescriptions();
std::array<VkVertexInputAttributeDescription, 2>	getInstanceAttributeDescriptions();

}