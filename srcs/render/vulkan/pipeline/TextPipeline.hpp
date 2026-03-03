#pragma once

#include <vector>

#include "APipeline.hpp"
#include "../VulkanContext.hpp"

namespace render::vulkan {
class TextPipeline : public APipeline {
public:
	constexpr static const char* vertShaderPath = "shaders/fontShader.vert.spv";
	constexpr static const char* fragShaderPath = "shaders/fontShader.frag.spv";

	TextPipeline(VulkanContext& context, const VkExtent2D& extent, VkRenderPass renderPass, const std::vector<VkDescriptorSetLayout>& descriptorSetLayouts = {});
	~TextPipeline() override;
};
}
