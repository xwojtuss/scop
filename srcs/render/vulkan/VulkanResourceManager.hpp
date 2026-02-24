#pragma once

#include <unordered_map>
#include <vulkan/vulkan.h>

#include "VulkanSwapchain.hpp"
#include "../../render/GpuTypes.hpp"
#include "../../assets/Resources.hpp"

namespace render::vulkan {

class VulkanContext;
class VulkanFrameData;

struct GpuMesh {
	VkBuffer		vertexBuffer;
	VkDeviceMemory	vertexMemory;
	VkBuffer		indexBuffer;
	VkDeviceMemory	indexMemory;
	uint32_t		indexCount;
};

struct GpuTexture {
	SwapChainImage	image;
	VkSampler		sampler;
	VkDescriptorSet	descriptorSet;
	uint32_t		mipLevels;
};

constexpr uint32_t	textureLimit = 10;

class VulkanResourceManager {
public:
	VulkanResourceManager(VulkanContext&);
	~VulkanResourceManager();
	
	VkCommandPool			getCommandPool() const;
	void					copyBuffer(VulkanContext& context, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	assets::MeshHandle		addMesh(const GpuMesh& meshData);
	assets::TextureHandle	createTexture(const assets::TextureData&, VulkanContext&, VulkanFrameData&);
	const GpuMesh&			getMesh(assets::MeshHandle handle) const;
	const GpuTexture&		getTexture(assets::TextureHandle handle) const;
	size_t					getTextureCount() const;
	void					cleanup(VulkanContext& context);
	
	static void				createBuffer(VulkanContext& context, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	
private:
	VkCommandPool								m_commandPool;
	std::unordered_map<uint64_t, GpuMesh>		m_meshes;
	std::unordered_map<uint64_t, GpuTexture>	m_textures;
	
	void					createCommandPool(const VulkanContext&);
	void					copyBufferToImage(VulkanContext& context, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
	void					generateMipmaps(VulkanContext& context, VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
	void					transitionImageLayout(const VulkanContext& context, VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
	SwapChainImage			createTextureImage(const assets::TextureData& textureData, VulkanContext& context);
	VkImageView				createTextureImageView(const assets::TextureData& textureData, const VulkanContext& context, VkImage textureImage);
	VkSampler				createTextureSampler(const VulkanContext& context);
};
}