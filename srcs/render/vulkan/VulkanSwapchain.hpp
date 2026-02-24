#pragma once

#include <algorithm>
#include <array>
#include <limits>
#include <vector>
#include <vulkan/vulkan.h>

#include "../../platform/window/IWindow.hpp"

namespace render::vulkan {

class VulkanContext;

struct SwapChainImage {
	VkImage			image;
	VkImageView		imageView;
	VkDeviceMemory	imageMemory;
};

class VulkanSwapchain {
private:
	VkSwapchainKHR				m_swapChain;
	std::vector<VkImage>		m_swapChainImages;
	std::vector<VkImageView>	m_swapChainImageViews;
	VkFormat					m_swapChainImageFormat;
	VkExtent2D					m_swapChainExtent;
	VkRenderPass				m_renderPass;
	std::vector<VkFramebuffer>	m_swapChainFramebuffers;
	SwapChainImage				m_colorImage;
	SwapChainImage				m_depthImage;

	void						createSwapChain(VulkanContext&);
	void						createImageViews(const VulkanContext&);
	void						createDepthResources(VulkanContext& context);
	void						createColorResources(VulkanContext& context);
	void						createRenderPass(const VulkanContext&);
	void						createFramebuffers(const VulkanContext&);
	void						cleanupSwapChain(const VulkanContext& context);
	
	static VkSurfaceFormatKHR	chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	static VkPresentModeKHR		chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	static VkExtent2D			chooseSwapExtent(const platform::window::IWindow& window, const VkSurfaceCapabilitiesKHR& capabilities);
	
public:
	VulkanSwapchain(VulkanContext&);
	~VulkanSwapchain();
	
	VkExtent2D					getExtent() const;
	VkRenderPass				getRenderPass() const;
	VkSwapchainKHR				getSwapChain() const;
	VkFramebuffer				getFramebuffer(uint32_t index) const;
	void						recreateSwapChain(VulkanContext& context);
	void						cleanup(const VulkanContext& context);

	static void			createImage(VulkanContext& context, VkExtent2D extent, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, SwapChainImage& swapChainImage);
	static VkImageView	createImageView(VkDevice device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
};
}