#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <stdexcept>

#include "../VulkanVertexUtils.hpp"
#include "../../../platform/filesystem/readFile.hpp"

namespace render::vulkan {
class APipeline {
protected:
	VkPipelineLayout	m_pipelineLayout;
	VkPipeline			m_pipeline;

	APipeline();
	
	static VkShaderModule							createShaderModule(const std::vector<char>& code, VkDevice device);
	static void										createShaderStages(VkDevice device, const char* vertPath, const char* fragPath, VkPipelineShaderStageCreateInfo& vertShaderStageInfo, VkPipelineShaderStageCreateInfo& fragShaderStageInfo);
	static VkRect2D									createScissor(const VkExtent2D& extent);
	static VkViewport								createViewport(const VkExtent2D& extent);
	static void										createViewportState(VkPipelineViewportStateCreateInfo& viewportState, VkPipelineDynamicStateCreateInfo& dynamicState, VkViewport& viewport, const VkRect2D& scissor, const std::vector<VkDynamicState>& dynamicStates);
	static VkPipelineInputAssemblyStateCreateInfo	createInputAssemblyState();
	static VkPipelineRasterizationStateCreateInfo	createRasterizationState();
	static VkPipelineMultisampleStateCreateInfo		createMultisampleState(VkSampleCountFlagBits msaaSamples);
	static VkPipelineColorBlendAttachmentState		createColorBlendAttachmentState();
	static VkPipelineColorBlendStateCreateInfo		createColorBlendState(VkPipelineColorBlendAttachmentState& colorBlendAttachment);
	static VkPipelineDepthStencilStateCreateInfo	createDepthStencilState();
	static VkPipelineLayoutCreateInfo				createPipelineLayoutInfo(const std::vector<VkDescriptorSetLayout>& descriptorSetLayouts, const VkPushConstantRange& pushConstantRange);
	template <int N>
	static void										destroyShaderStages(VkDevice device, std::array<VkPipelineShaderStageCreateInfo, N>& shaderStages);
	template <typename UBO>
	static VkPushConstantRange						createPushConstantRange();

public:
	virtual ~APipeline();

	const VkPipelineLayout&	getPipelineLayout() const;
	const VkPipeline&		getPipeline() const;
	void					cleanup(VkDevice device);
};
}

#include "APipeline.tpp"
