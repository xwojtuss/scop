#include "VulkanRenderer.hpp"

using namespace render::vulkan;

VulkanRenderer::VulkanRenderer(platform::window::IWindow& window) {
	setClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_context = std::make_unique<VulkanContext>(window);
	m_swapchain = std::make_unique<VulkanSwapchain>(*m_context);
	m_resourceManager = std::make_unique<VulkanResourceManager>(*m_context);
	m_frameData = std::make_unique<VulkanFrameData>(*m_context, *m_resourceManager);
	createPipeline();
	createTextPipeline();
	createTextMesh();
}

void	VulkanRenderer::createTextMesh() {
	m_textMeshHandle = createMesh({
		.vertices = {
			{{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
			{{1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
			{{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
			{{0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
		},
		.indices = {2, 1, 3, 3, 2, 4}
	});
}

VkShaderModule	VulkanRenderer::createShaderModule(const std::vector<char>& code, VkDevice device) {
	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
	VkShaderModule shaderModule;
	if (vkCreateShaderModule(device, &createInfo, NULL, &shaderModule) != VK_SUCCESS) {
		throw std::runtime_error("failed to create shader module!");
	}
	return shaderModule;
}

void VulkanRenderer::createPipeline() {
	auto vertShaderCode = readFile(vertShaderPath);
	auto fragShaderCode = readFile(fragShaderPath);

	VkShaderModule vertShaderModule = createShaderModule(vertShaderCode, m_context->getLogicalDevice());
	VkShaderModule fragShaderModule = createShaderModule(fragShaderCode, m_context->getLogicalDevice());

	VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
	vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;

	vertShaderStageInfo.module = vertShaderModule;
	vertShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
	fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragShaderStageInfo.module = fragShaderModule;
	fragShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

	(void)shaderStages;

	// Dynamic state

	std::vector<VkDynamicState> dynamicStates = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};

	VkPipelineDynamicStateCreateInfo dynamicState{};
	dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
	dynamicState.pDynamicStates = dynamicStates.data();

	// Vertex input

	VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

	auto bindingDescription = getBindingDescription();
	auto attributeDescriptions = getAttributeDescriptions();

	vertexInputInfo.vertexBindingDescriptionCount = 1;
	vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
	vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
	vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

	// Input assembly

	VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssembly.primitiveRestartEnable = VK_FALSE;

	// Viewport and scissors

	VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float) m_swapchain->getExtent().width;
	viewport.height = (float) m_swapchain->getExtent().height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	VkRect2D scissor{};
	scissor.offset = {0, 0};
	scissor.extent = m_swapchain->getExtent();

	VkPipelineViewportStateCreateInfo viewportState{};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.pViewports = &viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &scissor;

	//Rasterizer

	VkPipelineRasterizationStateCreateInfo rasterizer{};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 1.0f;
	rasterizer.depthBiasEnable = VK_FALSE;
	rasterizer.depthBiasConstantFactor = 0.0f;
	rasterizer.depthBiasClamp = 0.0f;
	rasterizer.depthBiasSlopeFactor = 0.0f;
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;

	// Multisampling

	VkPipelineMultisampleStateCreateInfo multisampling{};
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = m_context->getMsaaSamples();
	multisampling.minSampleShading = 1.0f;
	multisampling.pSampleMask = nullptr;
	multisampling.alphaToCoverageEnable = VK_FALSE;
	multisampling.alphaToOneEnable = VK_FALSE;

	// Color blending

	VkPipelineColorBlendAttachmentState colorBlendAttachment{};
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_TRUE;
	colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
	colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

	VkPipelineColorBlendStateCreateInfo colorBlending{};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.logicOp = VK_LOGIC_OP_COPY;
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &colorBlendAttachment;
	colorBlending.blendConstants[0] = 0.0f;
	colorBlending.blendConstants[1] = 0.0f;
	colorBlending.blendConstants[2] = 0.0f;
	colorBlending.blendConstants[3] = 0.0f;

	// Pipeline layout

	VkDescriptorSetLayout layouts[] = {
		m_frameData->getFrameDescriptorSetLayout(),
		m_frameData->getTextureDescriptorSetLayout()
	};

	VkPushConstantRange pushConstantRange{};
	pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	pushConstantRange.offset = 0;
	pushConstantRange.size = sizeof(ObjectUBO);
	
	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 2;
	pipelineLayoutInfo.pSetLayouts = layouts;
	pipelineLayoutInfo.pushConstantRangeCount = 1;
	pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
	

	if (vkCreatePipelineLayout(m_context->getLogicalDevice(), &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create pipeline layout!");
	}

	VkPipelineDepthStencilStateCreateInfo depthStencil{};
	depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	depthStencil.depthTestEnable = VK_TRUE;
	depthStencil.depthWriteEnable = VK_TRUE;
	depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
	depthStencil.depthBoundsTestEnable = VK_FALSE;
	depthStencil.minDepthBounds = 0.0f;
	depthStencil.maxDepthBounds = 1.0f;
	depthStencil.stencilTestEnable = VK_FALSE;
	depthStencil.front = {};
	depthStencil.back = {};
	
	VkGraphicsPipelineCreateInfo pipelineInfo{};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStages;
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssembly;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pDepthStencilState = nullptr;
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.pDynamicState = &dynamicState;
	pipelineInfo.layout = m_pipelineLayout;
	pipelineInfo.renderPass = m_swapchain->getRenderPass();
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
	pipelineInfo.basePipelineIndex = -1;
	pipelineInfo.pDepthStencilState = &depthStencil;

	if (vkCreateGraphicsPipelines(m_context->getLogicalDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_graphicsPipeline) != VK_SUCCESS) {
		throw std::runtime_error("failed to create graphics pipeline!");
	}

	vkDestroyShaderModule(m_context->getLogicalDevice(), fragShaderModule, nullptr);
	vkDestroyShaderModule(m_context->getLogicalDevice(), vertShaderModule, nullptr);
}

void	VulkanRenderer::createTextPipeline() {
	auto vertShaderCode = readFile(textVertShaderPath);
	auto fragShaderCode = readFile(textFragShaderPath);

	VkShaderModule vertShaderModule = createShaderModule(vertShaderCode, m_context->getLogicalDevice());
	VkShaderModule fragShaderModule = createShaderModule(fragShaderCode, m_context->getLogicalDevice());

	VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
	vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;

	vertShaderStageInfo.module = vertShaderModule;
	vertShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
	fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragShaderStageInfo.module = fragShaderModule;
	fragShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

	(void)shaderStages;

	// Dynamic state

	std::vector<VkDynamicState> dynamicStates = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};

	VkPipelineDynamicStateCreateInfo dynamicState{};
	dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
	dynamicState.pDynamicStates = dynamicStates.data();

	// Vertex input

	VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

	auto bindingDescription = getBindingDescription();
	auto attributeDescriptions = getAttributeDescriptions();

	vertexInputInfo.vertexBindingDescriptionCount = 1;
	vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
	vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
	vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

	// Input assembly

	VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssembly.primitiveRestartEnable = VK_FALSE;

	// Viewport and scissors

	VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float) m_swapchain->getExtent().width;
	viewport.height = (float) m_swapchain->getExtent().height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	VkRect2D scissor{};
	scissor.offset = {0, 0};
	scissor.extent = m_swapchain->getExtent();

	VkPipelineViewportStateCreateInfo viewportState{};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.pViewports = &viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &scissor;

	//Rasterizer

	VkPipelineRasterizationStateCreateInfo rasterizer{};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 1.0f;
	rasterizer.depthBiasEnable = VK_FALSE;
	rasterizer.depthBiasConstantFactor = 0.0f;
	rasterizer.depthBiasClamp = 0.0f;
	rasterizer.depthBiasSlopeFactor = 0.0f;
	rasterizer.cullMode = VK_CULL_MODE_NONE;
	rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;

	// Color blending

	VkPipelineColorBlendAttachmentState colorBlendAttachment{};
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_TRUE;
	colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
	colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

	VkPipelineColorBlendStateCreateInfo colorBlending{};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.logicOp = VK_LOGIC_OP_COPY;
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &colorBlendAttachment;
	colorBlending.blendConstants[0] = 0.0f;
	colorBlending.blendConstants[1] = 0.0f;
	colorBlending.blendConstants[2] = 0.0f;
	colorBlending.blendConstants[3] = 0.0f;

	// Pipeline layout

	VkDescriptorSetLayout layouts[] = {
		m_frameData->getFrameDescriptorSetLayout(),
		m_frameData->getTextureDescriptorSetLayout()
	};

	VkPushConstantRange pushConstantRange{};
	pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	pushConstantRange.offset = 0;
	pushConstantRange.size = sizeof(ObjectUBO);
	
	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 2;
	pipelineLayoutInfo.pSetLayouts = layouts;
	pipelineLayoutInfo.pushConstantRangeCount = 1;
	pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
	

	if (vkCreatePipelineLayout(m_context->getLogicalDevice(), &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create pipeline layout!");
	}

	VkPipelineDepthStencilStateCreateInfo depthStencil{};
	depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	depthStencil.depthTestEnable = VK_FALSE;
	depthStencil.depthWriteEnable = VK_FALSE;
	depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
	depthStencil.depthBoundsTestEnable = VK_FALSE;
	depthStencil.minDepthBounds = 0.0f;
	depthStencil.maxDepthBounds = 1.0f;
	depthStencil.stencilTestEnable = VK_FALSE;
	depthStencil.front = {};
	depthStencil.back = {};
	
	VkGraphicsPipelineCreateInfo pipelineInfo{};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStages;
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssembly;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = nullptr;
	pipelineInfo.pDepthStencilState = nullptr;
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.pDynamicState = &dynamicState;
	pipelineInfo.layout = m_pipelineLayout;
	pipelineInfo.renderPass = m_swapchain->getRenderPass();
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
	pipelineInfo.basePipelineIndex = -1;
	pipelineInfo.pDepthStencilState = &depthStencil;

	if (vkCreateGraphicsPipelines(m_context->getLogicalDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_textPipeline) != VK_SUCCESS) {
		throw std::runtime_error("failed to create text pipeline!");
	}

	vkDestroyShaderModule(m_context->getLogicalDevice(), fragShaderModule, nullptr);
	vkDestroyShaderModule(m_context->getLogicalDevice(), vertShaderModule, nullptr);
}

assets::MeshHandle	VulkanRenderer::createMesh(const assets::MeshData& meshData) {
	GpuMesh mesh;

	m_frameData->createVertexBuffer(*m_context, *m_resourceManager, meshData, mesh);
	m_frameData->createIndexBuffer(*m_context, *m_resourceManager, meshData, mesh);
	
	assets::MeshHandle handle = m_resourceManager->addMesh(mesh);

	return handle;
}

assets::TextureHandle	VulkanRenderer::createTexture(const assets::TextureData& textureData) {
	return m_resourceManager->createTexture(textureData, *m_context, *m_frameData);
}

void	VulkanRenderer::drawMesh(const assets::MeshHandle& mesh, const assets::TextureHandle& texture, const ecs::component::Transform& transform) {
	VkBuffer vertexBuffer = m_resourceManager->getMesh(mesh).vertexBuffer;
	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(m_frameData->getCurrentCommandBuffer(), 0, 1, &vertexBuffer, &offset);

	vkCmdBindIndexBuffer(m_frameData->getCurrentCommandBuffer(), m_resourceManager->getMesh(mesh).indexBuffer, 0, VK_INDEX_TYPE_UINT32);

	vkCmdBindDescriptorSets(m_frameData->getCurrentCommandBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipelineLayout, 1, 1, &m_resourceManager->getTexture(texture).descriptorSet, 0, nullptr);

	// Push constants for object transform
	ObjectUBO objectUbo{};
	objectUbo.model = transform.toModelMatrix();
	vkCmdPushConstants(m_frameData->getCurrentCommandBuffer(), m_pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(ObjectUBO), &objectUbo);

	vkCmdDrawIndexed(m_frameData->getCurrentCommandBuffer(), static_cast<uint32_t>(m_resourceManager->getMesh(mesh).indexCount), 1, 0, 0, 0);
}

void	VulkanRenderer::drawText(const std::string& text, const assets::TextureHandle& font, const ecs::component::Transform2D& transform, const ecs::component::Color* color = nullptr) {
	VkBuffer vertexBuffer = m_resourceManager->getMesh(m_textMeshHandle).vertexBuffer;
	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(m_frameData->getCurrentCommandBuffer(), 0, 1, &vertexBuffer, &offset);

	vkCmdBindIndexBuffer(m_frameData->getCurrentCommandBuffer(), m_resourceManager->getMesh(m_textMeshHandle).indexBuffer, 0, VK_INDEX_TYPE_UINT32);

	vkCmdBindDescriptorSets(m_frameData->getCurrentCommandBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipelineLayout, 1, 1, &m_resourceManager->getTexture(font).descriptorSet, 0, nullptr);

	TextUBO ubo{};
	ubo.color = color ? color->color : glm::vec4(1.0f);
	ubo.position = transform.position;
	ubo.size = transform.scale;
	vkCmdPushConstants(m_frameData->getCurrentCommandBuffer(), m_pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(TextUBO), &ubo);

	vkCmdDrawIndexed(m_frameData->getCurrentCommandBuffer(), static_cast<uint32_t>(m_resourceManager->getMesh(m_textMeshHandle).indexCount), 1, 0, 0, 0);
}

void	VulkanRenderer::updateCamera(const component::Camera& camera) {
	FrameUBO frameUbo{};

	frameUbo.view = camera.view;
	frameUbo.proj = camera.projection;
	frameUbo.proj[1][1] *= -1;

	memcpy(m_frameData->getCurrentMappedFrameUBO(), &frameUbo, sizeof(frameUbo));
}

void	VulkanRenderer::recordCurrentCommandBuffer(ecs::SystemManager& systemManager, uint32_t currentFrame) {
	if (!m_frameIndex.has_value()) return;

	VkCommandBuffer commandBuffer = m_frameData->getCurrentCommandBuffer();

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = 0;
	beginInfo.pInheritanceInfo = nullptr;

	if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
		throw std::runtime_error("failed to begin recording command buffer!");
	}

	VkRenderPassBeginInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = m_swapchain->getRenderPass();
	renderPassInfo.framebuffer = m_swapchain->getFramebuffer(m_frameIndex.value());
	renderPassInfo.renderArea.offset = {0, 0};
	renderPassInfo.renderArea.extent = m_swapchain->getExtent();

	renderPassInfo.clearValueCount = static_cast<uint32_t>(m_clearValues.size());
	renderPassInfo.pClearValues = m_clearValues.data();

	vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_graphicsPipeline);

	VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = static_cast<float>(m_swapchain->getExtent().width);
	viewport.height = static_cast<float>(m_swapchain->getExtent().height);
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

	VkRect2D scissor{};
	scissor.offset = {0, 0};
	scissor.extent = m_swapchain->getExtent();
	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
	
	vkCmdBindDescriptorSets(m_frameData->getCurrentCommandBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipelineLayout, 0, 1, m_frameData->getDescriptorSet(currentFrame), 0, nullptr);
	
	systemManager.onRendererDraw(*this);

	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_textPipeline);
	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
	vkCmdBindDescriptorSets(m_frameData->getCurrentCommandBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipelineLayout, 0, 1, m_frameData->getDescriptorSet(currentFrame), 0, nullptr);

	systemManager.onTextDraw(*this);

	vkCmdEndRenderPass(m_frameData->getCurrentCommandBuffer());
	if (vkEndCommandBuffer(m_frameData->getCurrentCommandBuffer()) != VK_SUCCESS) {
		throw std::runtime_error("failed to record command buffer!");
	vkCmdDrawIndexed(m_frameData->getCurrentCommandBuffer(), static_
	}
}

void	VulkanRenderer::beginFrame() {
	m_frameIndex = 0;

	m_frameData->waitForFences(*m_context, m_frameData->getCurrentFrame());

	VkResult result = vkAcquireNextImageKHR(m_context->getLogicalDevice(), m_swapchain->getSwapChain(), UINT64_MAX, m_frameData->getCurrentImageAvailableSemaphore(), VK_NULL_HANDLE, &m_frameIndex.value());


	if (result == VK_ERROR_OUT_OF_DATE_KHR) {
		vkDeviceWaitIdle(m_context->getLogicalDevice());
		vkDestroyPipeline(m_context->getLogicalDevice(), m_graphicsPipeline, nullptr);
		vkDestroyPipeline(m_context->getLogicalDevice(), m_textPipeline, nullptr);
		vkDestroyPipelineLayout(m_context->getLogicalDevice(), m_pipelineLayout, nullptr);
		
		m_swapchain->recreateSwapChain(*m_context);
		createPipeline();
		createTextPipeline();
		
		m_frameIndex.reset();
		return;
	} else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
		throw std::runtime_error("failed to acquire swap chain image!");
	}
}

void	VulkanRenderer::render(ecs::SystemManager& systemManager) {
	if (!m_frameIndex.has_value()) return;

	systemManager.onRendererFrame(*this);

	// Only reset the fence if we are submitting work
	m_frameData->resetFences(*m_context, m_frameData->getCurrentFrame());
	
	vkResetCommandBuffer(m_frameData->getCurrentCommandBuffer(), 0);
	recordCurrentCommandBuffer(systemManager, m_frameData->getCurrentFrame());
}

void	VulkanRenderer::endFrame() {
	if (!m_frameIndex.has_value()) return;

	VkSemaphore signalSemaphore = m_frameData->submitCommandBuffer(*m_context);

	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &signalSemaphore;

	VkSwapchainKHR swapChains[] = {m_swapchain->getSwapChain()};
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &m_frameIndex.value();
	presentInfo.pResults = nullptr;

	VkResult result = vkQueuePresentKHR(m_context->getPresentQueue(), &presentInfo);

	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_context->getWindow().wasResized()) {
		vkDeviceWaitIdle(m_context->getLogicalDevice());
		vkDestroyPipeline(m_context->getLogicalDevice(), m_graphicsPipeline, nullptr);
		vkDestroyPipeline(m_context->getLogicalDevice(), m_textPipeline, nullptr);
		vkDestroyPipelineLayout(m_context->getLogicalDevice(), m_pipelineLayout, nullptr);
		
		m_swapchain->recreateSwapChain(*m_context);
		createPipeline();
		createTextPipeline();
	} else if (result != VK_SUCCESS) {
		throw std::runtime_error("failed to present swap chain image!");
	}

	m_frameData->incrementCurrentFrame();
}

void	VulkanRenderer::setClearColor(float r, float g, float b, float a) {
	m_clearValues[0].color = {{r, g, b, a}};
	m_clearValues[1].depthStencil = {1.0f, 0};
}

const assets::MeshHandle&	VulkanRenderer::getTextMeshHandle() const {
	return m_textMeshHandle;
}

void	VulkanRenderer::cleanup() {
	vkDeviceWaitIdle(m_context->getLogicalDevice());

	m_resourceManager->cleanup(*m_context);
	m_frameData->cleanup(*m_context);
	m_swapchain->cleanup(*m_context);

	vkDestroyPipeline(m_context->getLogicalDevice(), m_graphicsPipeline, nullptr);
	vkDestroyPipeline(m_context->getLogicalDevice(), m_textPipeline, nullptr);
	vkDestroyPipelineLayout(m_context->getLogicalDevice(), m_pipelineLayout, nullptr);
}

VulkanRenderer::~VulkanRenderer() {
	cleanup();
}
