#include "TextPipeline.hpp"

using namespace render::vulkan;

TextPipeline::TextPipeline(VulkanContext& context, const VkExtent2D& extent, VkRenderPass renderPass, const std::vector<VkDescriptorSetLayout>& descriptorSetLayouts) : APipeline() {
	constexpr std::size_t shaderStageCount = 2;
	std::array<VkPipelineShaderStageCreateInfo, shaderStageCount> shaderStages{};
	VkPipelineViewportStateCreateInfo viewportState;
	VkPipelineDynamicStateCreateInfo dynamicState;

	APipeline::createShaderStages(context.getLogicalDevice(), vertShaderPath, fragShaderPath, shaderStages[0], shaderStages[1]);
	APipeline::createViewport(extent);
	APipeline::createScissor(extent);
	std::vector<VkDynamicState> dynamicStates = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};
	APipeline::createViewportState(viewportState, dynamicState, dynamicStates);

	auto pipelineLayoutInfo = APipeline::createPipelineLayoutInfo(descriptorSetLayouts, createPushConstantRange<ObjectUBO>());

	if (vkCreatePipelineLayout(context.getLogicalDevice(), &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create pipeline layout!");
	}

	VkGraphicsPipelineCreateInfo pipelineInfo{};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = static_cast<uint32_t>(shaderStages.size());
	pipelineInfo.pStages = shaderStages.data();
	VkPipelineVertexInputStateCreateInfo vertexInputState = {};
	auto bindingDescription = getBindingDescription();
	auto attributeDescriptions = getAttributeDescriptions();
	auto perInstanceBindingDescription = getInstanceBindingDescription();
	auto perInstanceAttributeDescriptions = getInstanceAttributeDescriptions();
	auto bindingDescriptions = std::array<VkVertexInputBindingDescription, 2>{bindingDescription, perInstanceBindingDescription};
	auto attributeDescriptionsCombined = std::vector<VkVertexInputAttributeDescription>{};
	attributeDescriptionsCombined.insert(attributeDescriptionsCombined.end(), attributeDescriptions.begin(), attributeDescriptions.end());
	attributeDescriptionsCombined.insert(attributeDescriptionsCombined.end(), perInstanceAttributeDescriptions.begin(), perInstanceAttributeDescriptions.end());
	vertexInputState.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputState.vertexBindingDescriptionCount = 2;
	vertexInputState.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptionsCombined.size());
	vertexInputState.pVertexBindingDescriptions = bindingDescriptions.data();
	vertexInputState.pVertexAttributeDescriptions = attributeDescriptionsCombined.data();
	pipelineInfo.pVertexInputState = &vertexInputState;
	auto inputAssemblyState = APipeline::createInputAssemblyState();
	pipelineInfo.pInputAssemblyState = &inputAssemblyState;
	pipelineInfo.pViewportState = &viewportState;
	auto rasterizationState = APipeline::createRasterizationState();
	rasterizationState.cullMode = VK_CULL_MODE_NONE;
	pipelineInfo.pRasterizationState = &rasterizationState;
	auto multisampleState = APipeline::createMultisampleState(context.getMsaaSamples());
	pipelineInfo.pMultisampleState = &multisampleState;
	pipelineInfo.pDepthStencilState = nullptr;
	auto colorBlendAttachmentState = APipeline::createColorBlendAttachmentState();
	auto colorBlendState = APipeline::createColorBlendState(colorBlendAttachmentState);
	pipelineInfo.pColorBlendState = &colorBlendState;
	pipelineInfo.pDynamicState = &dynamicState;
	pipelineInfo.layout = m_pipelineLayout;
	pipelineInfo.renderPass = renderPass;
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
	pipelineInfo.basePipelineIndex = -1;
	auto depthStencil = APipeline::createDepthStencilState();
	depthStencil.depthTestEnable = VK_FALSE;
	depthStencil.depthWriteEnable = VK_FALSE;
	pipelineInfo.pDepthStencilState = &depthStencil;

	if (vkCreateGraphicsPipelines(context.getLogicalDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_pipeline) != VK_SUCCESS) {
		throw std::runtime_error("failed to create graphics pipeline!");
	}

	APipeline::destroyShaderStages<shaderStageCount>(context.getLogicalDevice(), shaderStages);
}

TextPipeline::~TextPipeline() {
}
