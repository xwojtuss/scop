#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#ifdef _WIN32
# define GLFW_EXPOSE_NATIVE_WIN32
# include <GLFW/glfw3native.h>
#endif

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define APP_NAME "scop"

#include <algorithm>
#include <fstream>
#include <limits>
#include <optional>
#include <set>
#include <stdexcept>
#include <vector>
#include <cstring>

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	/**
	 * The validation layers will print debug messages by default
	 * but we can also specify a callback function to handle them
	 */
	const bool enableValidationLayers = true;
#endif

struct QueueFamilyIndices {
	std::optional<uint32_t>	graphicsFamily;
	std::optional<uint32_t>	presentFamily;

	bool					isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR		capabilities;
	std::vector<VkSurfaceFormatKHR>	formats;
	std::vector<VkPresentModeKHR>	presentModes;
};


class Renderer {
	private:
		GLFWwindow*					window;
		VkInstance					instance;
		VkDevice					device;
		VkQueue						graphicsQueue;
		VkQueue						presentQueue;
		VkSurfaceKHR				surface;
		VkSwapchainKHR				swapChain;
		std::vector<VkImage>		swapChainImages;
		std::vector<VkImageView>	swapChainImageViews;
		VkFormat					swapChainImageFormat;
		VkExtent2D					swapChainExtent;
		VkRenderPass				renderPass;
		VkPipelineLayout			pipelineLayout;
		VkPipeline					graphicsPipeline;

		static const std::vector<const char*>	deviceExtensions;
		static const std::vector<const char*>	validationLayers;

		void					initWindow();
		void					initVulkan();
		void					createInstance();
		void					createRenderPass();
		VkPhysicalDevice		pickPhysicalDevice();
		QueueFamilyIndices		findQueueFamilies(VkPhysicalDevice physicalDevice);
		void					createLogicalDevice(VkPhysicalDevice physicalDevice);
		bool					isDeviceSuitable(VkPhysicalDevice device);
		bool					checkDeviceExtensionSupport(VkPhysicalDevice device);
		SwapChainSupportDetails	querySwapChainSupport(VkPhysicalDevice device);
		VkSurfaceFormatKHR		chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR		chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D				chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		void					createSwapChain(VkPhysicalDevice physicalDevice);
		void					createImageViews();
		void					createSurface();
		void					createGraphicsPipeline();
		VkShaderModule			createShaderModule(const std::vector<char>& code);
		bool					checkValidationLayerSupport();
		void					mainLoop();
		void					cleanup();

	public:
		void				run();
};

std::vector<char>	readFile(const std::string& filename);