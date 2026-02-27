#include "VulkanFrameData.hpp"
#include "VulkanContext.hpp"
#include "VulkanResourceManager.hpp"

using namespace render::vulkan;

VulkanFrameData::VulkanFrameData(VulkanContext& context, VulkanResourceManager& resourceManager) : m_currentFrame(0) {
	createFrameDescriptorSetLayout(context);
	createTextureDescriptorSetLayout(context);
	createDescriptorPool(context);
	createFrameUBOs(const_cast<VulkanContext&>(context));
	createFrameDescriptorSets(context);
	createCommandBuffers(context, resourceManager);
	createSyncObjects(context);
}

VkCommandBuffer	VulkanFrameData::beginSingleTimeCommands(VkCommandPool commandPool, VkDevice device) {
	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = commandPool;
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;
	vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(commandBuffer, &beginInfo);

	return commandBuffer;
}

void	VulkanFrameData::endSingleTimeCommands(VkCommandBuffer commandBuffer, VkCommandPool commandPool, VkQueue graphicsQueue, VkDevice device) {
	vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(graphicsQueue);

	vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
}

void	VulkanFrameData::createFrameUBOs(VulkanContext& context) {
	VkDeviceSize bufferSize = sizeof(FrameUBO);

	m_frameUBOs.resize(maxFramesInFlight);
	m_frameUBOsMemory.resize(maxFramesInFlight);
	m_frameUBOsMapped.resize(maxFramesInFlight);

	for (size_t i = 0; i < maxFramesInFlight; i++) {
		VulkanResourceManager::createBuffer(context, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_frameUBOs[i], m_frameUBOsMemory[i]);

		vkMapMemory(context.getLogicalDevice(), m_frameUBOsMemory[i], 0, bufferSize, 0, &m_frameUBOsMapped[i]);
	}
}

void	VulkanFrameData::createFrameDescriptorSetLayout(const VulkanContext& context) {
	VkDescriptorSetLayoutBinding uboBinding{};
	uboBinding.binding = 0;
	uboBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	uboBinding.descriptorCount = 1;
	uboBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	uboBinding.pImmutableSamplers = nullptr;

	VkDescriptorSetLayoutCreateInfo layoutInfo{};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = 1;
	layoutInfo.pBindings = &uboBinding;

	if (vkCreateDescriptorSetLayout(context.getLogicalDevice(), &layoutInfo, nullptr, &m_frameSetLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create frame descriptor set layout");
	}
}

void	VulkanFrameData::createFrameDescriptorSets(const VulkanContext& context) {
	std::vector<VkDescriptorSetLayout> layouts(
		maxFramesInFlight,
		m_frameSetLayout
	);

	VkDescriptorSetAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = m_descriptorPool;
	allocInfo.descriptorSetCount =
		static_cast<uint32_t>(layouts.size());
	allocInfo.pSetLayouts = layouts.data();

	m_frameDescriptorSets.resize(layouts.size());

	if (vkAllocateDescriptorSets(
			context.getLogicalDevice(),
			&allocInfo,
			m_frameDescriptorSets.data()) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to allocate frame descriptor sets");
	}

	for (size_t i = 0; i < layouts.size(); ++i)
	{
		VkDescriptorBufferInfo bufferInfo{};
		bufferInfo.buffer = m_frameUBOs[i];
		bufferInfo.offset = 0;
		bufferInfo.range = sizeof(FrameUBO);

		VkWriteDescriptorSet write{};
		write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		write.dstSet = m_frameDescriptorSets[i];
		write.dstBinding = 0;
		write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		write.descriptorCount = 1;
		write.pBufferInfo = &bufferInfo;

		vkUpdateDescriptorSets(
			context.getLogicalDevice(),
			1,
			&write,
			0,
			nullptr);
	}
}

void	VulkanFrameData::createTextureDescriptorSetLayout(const VulkanContext& context) {
	VkDescriptorSetLayoutBinding samplerBinding{};
	samplerBinding.binding = 0;
	samplerBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	samplerBinding.descriptorCount = 1;
	samplerBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
	samplerBinding.pImmutableSamplers = nullptr;

	VkDescriptorSetLayoutCreateInfo layoutInfo{};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = 1;
	layoutInfo.pBindings = &samplerBinding;

	if (vkCreateDescriptorSetLayout(context.getLogicalDevice(), &layoutInfo, nullptr, &m_textureSetLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create texture descriptor set layout");
	}
}

void	VulkanFrameData::createDescriptorPool(const VulkanContext& context) {
	std::array<VkDescriptorPoolSize, 2> poolSizes{};
	poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[0].descriptorCount = static_cast<uint32_t>(maxFramesInFlight);
	poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	poolSizes[1].descriptorCount = static_cast<uint32_t>(textureLimit);

	VkDescriptorPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
	poolInfo.pPoolSizes = poolSizes.data();
	poolInfo.maxSets = static_cast<uint32_t>(maxFramesInFlight + textureLimit);

	if (vkCreateDescriptorPool(context.getLogicalDevice(), &poolInfo, nullptr, &m_descriptorPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor pool!");
	}
}

VkDescriptorSetLayout	VulkanFrameData::getFrameDescriptorSetLayout() const {
	return m_frameSetLayout;
}

VkDescriptorSetLayout	VulkanFrameData::getTextureDescriptorSetLayout() const {
	return m_textureSetLayout;
}

VkDescriptorSet	VulkanFrameData::createTextureDescriptorSet(const VulkanContext& context) {
	VkDescriptorSetAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = m_descriptorPool;
	allocInfo.descriptorSetCount = 1;
	allocInfo.pSetLayouts = &m_textureSetLayout;

	VkDescriptorSet descriptorSet;

	if (vkAllocateDescriptorSets(context.getLogicalDevice(), &allocInfo, &descriptorSet) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate texture descriptor set");
	}
	return descriptorSet;
}

void	VulkanFrameData::createVertexBuffer(VulkanContext& context, VulkanResourceManager& resourceManager, const assets::MeshData& meshData, GpuMesh& mesh) {
	VkDeviceSize bufferSize = sizeof(meshData.vertices[0]) * meshData.vertices.size();

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	VulkanResourceManager::createBuffer(context, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(context.getLogicalDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, meshData.vertices.data(), (size_t) bufferSize);
	vkUnmapMemory(context.getLogicalDevice(), stagingBufferMemory);

	VulkanResourceManager::createBuffer(context, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, mesh.vertexBuffer, mesh.vertexMemory);

	resourceManager.copyBuffer(context, stagingBuffer, mesh.vertexBuffer, bufferSize);

	vkDestroyBuffer(context.getLogicalDevice(), stagingBuffer, nullptr);
	vkFreeMemory(context.getLogicalDevice(), stagingBufferMemory, nullptr);
}

void	VulkanFrameData::createIndexBuffer(VulkanContext& context, VulkanResourceManager& resourceManager, const assets::MeshData& meshData, GpuMesh& mesh) {
	VkDeviceSize bufferSize = sizeof(meshData.indices[0]) * meshData.indices.size();

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	VulkanResourceManager::createBuffer(context, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(context.getLogicalDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, meshData.indices.data(), (size_t) bufferSize);
	vkUnmapMemory(context.getLogicalDevice(), stagingBufferMemory);

	VulkanResourceManager::createBuffer(context, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, mesh.indexBuffer, mesh.indexMemory);

	resourceManager.copyBuffer(context, stagingBuffer, mesh.indexBuffer, bufferSize);

	vkDestroyBuffer(context.getLogicalDevice(), stagingBuffer, nullptr);
	vkFreeMemory(context.getLogicalDevice(), stagingBufferMemory, nullptr);
	
	mesh.indexCount = static_cast<uint32_t>(meshData.indices.size());
}

void	VulkanFrameData::createCommandBuffers(VulkanContext& context, VulkanResourceManager& resourceManager) {
	m_commandBuffers.resize(maxFramesInFlight);
	VkCommandBufferAllocateInfo allocInfo{};

	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = resourceManager.getCommandPool();
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t) m_commandBuffers.size();

	if (vkAllocateCommandBuffers(context.getLogicalDevice(), &allocInfo, m_commandBuffers.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}
}

void	VulkanFrameData::createSyncObjects(const VulkanContext& context) {
	m_imageAvailableSemaphores.resize(maxFramesInFlight);
	m_renderFinishedSemaphores.resize(maxFramesInFlight);
	m_inFlightFences.resize(maxFramesInFlight);

	VkSemaphoreCreateInfo semaphoreInfo{};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo fenceInfo{};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (std::size_t i = 0; i < maxFramesInFlight; i++) {
		if (vkCreateSemaphore(context.getLogicalDevice(), &semaphoreInfo, nullptr, &m_imageAvailableSemaphores[i]) != VK_SUCCESS ||
			vkCreateSemaphore(context.getLogicalDevice(), &semaphoreInfo, nullptr, &m_renderFinishedSemaphores[i]) != VK_SUCCESS ||
			vkCreateFence(context.getLogicalDevice(), &fenceInfo, nullptr, &m_inFlightFences[i]) != VK_SUCCESS) {

			throw std::runtime_error("failed to create synchronization objects for a frame!");
		}
	}
}

VkCommandBuffer	VulkanFrameData::getCommandBuffer(uint32_t index) const {
	return m_commandBuffers[index];
}

VkCommandBuffer	VulkanFrameData::getCurrentCommandBuffer() const {
	return m_commandBuffers[m_currentFrame];
}

VkResult	VulkanFrameData::waitForFences(VulkanContext& context, uint32_t currentFrame) {
	return vkWaitForFences(context.getLogicalDevice(), 1, &m_inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
}

void	VulkanFrameData::resetFences(VulkanContext& context, uint32_t currentFrame) {
	vkResetFences(context.getLogicalDevice(), 1, &m_inFlightFences[currentFrame]);
}

void	VulkanFrameData::incrementCurrentFrame() {
	m_currentFrame = (m_currentFrame + 1) % maxFramesInFlight;
}

VkSemaphore	VulkanFrameData::submitCommandBuffer(VulkanContext& context) {
	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = {m_imageAvailableSemaphores[m_currentFrame]};
	VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &m_commandBuffers[m_currentFrame];


	VkSemaphore signalSemaphores[] = {m_renderFinishedSemaphores[m_currentFrame]};
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	if (vkQueueSubmit(context.getGraphicsQueue(), 1, &submitInfo, m_inFlightFences[m_currentFrame]) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit draw command buffer!");
	}

	return signalSemaphores[0];
}

VkDescriptorSet*	VulkanFrameData::getDescriptorSet(uint32_t frameIndex) {
	return &m_frameDescriptorSets[frameIndex];
}

VkSemaphore	VulkanFrameData::getCurrentImageAvailableSemaphore() const {
	return m_imageAvailableSemaphores[m_currentFrame];
}

VkSemaphore	VulkanFrameData::getCurrentRenderFinishedSemaphore() const {
	return m_renderFinishedSemaphores[m_currentFrame];
}

uint32_t	VulkanFrameData::getCurrentFrame() const {
	return m_currentFrame;
}

void*	VulkanFrameData::getCurrentMappedFrameUBO() {
	return m_frameUBOsMapped[m_currentFrame];
}

void	VulkanFrameData::cleanup(VulkanContext& context) {
	for (size_t i = 0; i < maxFramesInFlight; i++) {
		vkDestroyBuffer(context.getLogicalDevice(), m_frameUBOs[i], nullptr);
		vkFreeMemory(context.getLogicalDevice(), m_frameUBOsMemory[i], nullptr);
		vkDestroySemaphore(context.getLogicalDevice(), m_imageAvailableSemaphores[i], nullptr);
		vkDestroySemaphore(context.getLogicalDevice(), m_renderFinishedSemaphores[i], nullptr);
		vkDestroyFence(context.getLogicalDevice(), m_inFlightFences[i], nullptr);
	}

	vkDestroyDescriptorPool(context.getLogicalDevice(), m_descriptorPool, nullptr);
	vkDestroyDescriptorSetLayout(context.getLogicalDevice(), m_frameSetLayout, nullptr);
	vkDestroyDescriptorSetLayout(context.getLogicalDevice(), m_textureSetLayout, nullptr);
}