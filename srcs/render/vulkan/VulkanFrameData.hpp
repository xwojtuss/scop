#pragma once

#include <chrono>
#include <vector>
#include <vulkan/vulkan.h>

#include "../../render/GpuTypes.hpp"
#include "../../assets/Resources.hpp"
#include "../../scene/Scene.hpp"

namespace render::vulkan {

class VulkanContext;
class VulkanResourceManager;
struct GpuMesh;

constexpr unsigned int	maxFramesInFlight = 2;

class VulkanFrameData {
private:
	std::vector<VkCommandBuffer>	m_commandBuffers;
	std::vector<VkSemaphore>		m_imageAvailableSemaphores;
	std::vector<VkSemaphore>		m_renderFinishedSemaphores;
	std::vector<VkFence>			m_inFlightFences;
	std::vector<VkBuffer>			m_frameUBOs;
	std::vector<VkDeviceMemory>		m_frameUBOsMemory;
	std::vector<void*>				m_frameUBOsMapped;
	VkDescriptorPool				m_descriptorPool;
	std::vector<VkDescriptorSet>	m_frameDescriptorSets;
	VkDescriptorSetLayout			m_frameSetLayout;
	VkDescriptorSetLayout			m_textureSetLayout;
	uint32_t						m_currentFrame;

	void	createFrameUBOs(VulkanContext&);
	void	createCommandBuffers(VulkanContext&, VulkanResourceManager& resourceManager);
	void	createSyncObjects(const VulkanContext&);
	void	createFrameDescriptorSets(const VulkanContext&);
	void	createFrameDescriptorSetLayout(const VulkanContext& context);
	void	createTextureDescriptorSetLayout(const VulkanContext& context);
	void	createDescriptorPool(const VulkanContext&);
	
public:
	VulkanFrameData(VulkanContext&, VulkanResourceManager&);
	
	VkDescriptorSetLayout	getFrameDescriptorSetLayout() const;
	VkDescriptorSetLayout	getTextureDescriptorSetLayout() const;
	VkDescriptorSet			createTextureDescriptorSet(const VulkanContext& context);
	void					createVertexBuffer(VulkanContext&, VulkanResourceManager& resourceManager, const assets::MeshData& meshData, GpuMesh& mesh);
	void					createIndexBuffer(VulkanContext&, VulkanResourceManager& resourceManager, const assets::MeshData& meshData, GpuMesh& mesh);
	VkResult				waitForFences(VulkanContext& context, uint32_t currentFrame);
	void					resetFences(VulkanContext& context, uint32_t currentFrame);
	VkCommandBuffer			getCommandBuffer(uint32_t currentFrame) const;
	VkCommandBuffer			getCurrentCommandBuffer() const;
	void					incrementCurrentFrame();
	void					updateFrameUBO(scene::Camera& camera, float aspectRatio);
	VkSemaphore				submitCommandBuffer(VulkanContext& context);
	void					applyObjectTransform(const scene::Renderable&, VkPipelineLayout pipelineLayout);
	uint32_t				getCurrentFrame() const;
	VkDescriptorSet*		getDescriptorSet(uint32_t frameIndex);
	VkSemaphore				getCurrentImageAvailableSemaphore() const;
	VkSemaphore				getCurrentRenderFinishedSemaphore() const;
	void					cleanup(VulkanContext& context);

	static VkCommandBuffer	beginSingleTimeCommands(VkCommandPool commandPool, VkDevice device);
	static void				endSingleTimeCommands(VkCommandBuffer commandBuffer, VkCommandPool commandPool, VkQueue graphicsQueue, VkDevice device);
};
}
