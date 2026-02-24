#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <optional>
#include <set>
#include <stdexcept>
#include <GLFW/glfw3.h> // For glfwCreateWindowSurface

#include "VulkanValidationLayers.hpp"
#include "../../platform/window/IWindow.hpp"
#include "../../app/ApplicationInfo.hpp"

namespace render::vulkan {

typedef std::vector<const char*>	DeviceExtensions;

struct QueueFamilyIndices {
	std::optional<uint32_t>	graphicsFamily;
	std::optional<uint32_t>	presentFamily;

	bool					isComplete();
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR		capabilities;
	std::vector<VkSurfaceFormatKHR>	formats;
	std::vector<VkPresentModeKHR>	presentModes;
};

class VulkanContext {
private:
	platform::window::IWindow&	m_window;
	VkInstance					m_instance;
	VkPhysicalDevice			m_physicalDevice;
	VkDevice					m_logicalDevice;
	VkQueue						m_graphicsQueue;
	VkQueue						m_presentQueue;
	VkSurfaceKHR				m_surface;
	SwapChainSupportDetails		m_swapChainSupport;
	QueueFamilyIndices			m_queueFamilyIndices;
	VkSampleCountFlagBits		m_msaaSamples = VK_SAMPLE_COUNT_1_BIT;
	std::optional<uint32_t>		m_memoryType;
	
	void	createInstance();
	void	createSurface();
	void	updateMaxUsableSampleCount();
	bool	isSuitable(VkPhysicalDevice device);
	bool	checkExtensionSupport(VkPhysicalDevice device) const;

public:
	static const DeviceExtensions			deviceExtensions;

	VulkanContext(platform::window::IWindow&);
	~VulkanContext();

	void							choosePhysicalDevice();
	void							createLogicalDevice();
	uint32_t						findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	VkFormat						findDepthFormat() const;
	VkFormat						findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features) const;
	QueueFamilyIndices				findQueueFamilies(VkPhysicalDevice device);
	SwapChainSupportDetails			querySwapChainSupport(VkPhysicalDevice device);
	const QueueFamilyIndices&		getQueueFamilyIndices() const;
	const VkSurfaceKHR&				getSurface() const;
	const VkDevice&					getLogicalDevice() const;
	const VkPhysicalDevice&			getPhysicalDevice() const;
	const VkQueue&					getGraphicsQueue() const;
	const VkQueue&					getPresentQueue() const;
	platform::window::IWindow&		getWindow();
	const VkSampleCountFlagBits&	getMsaaSamples() const;
};
}
