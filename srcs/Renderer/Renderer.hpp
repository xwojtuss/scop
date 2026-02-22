#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifdef _WIN32
# define GLFW_EXPOSE_NATIVE_WIN32
# include <GLFW/glfw3native.h>
#endif

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define APP_NAME "scop"

#define MODEL_PATH "models/room.obj"
#define TEXTURE_PATH "textures/room.png"

#include <algorithm>
#include <fstream>
#include <limits>
#include <optional>
#include <set>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <chrono>
#include <unordered_map>

#include "Vertex.hpp"
#include "UniformBufferObject.hpp"

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
		VkDescriptorSetLayout		descriptorSetLayout;
		VkPipelineLayout			pipelineLayout;
		VkPipeline					graphicsPipeline;
		std::vector<VkFramebuffer>	swapChainFramebuffers;
		VkCommandPool				commandPool;
		std::vector<VkCommandBuffer>	commandBuffers;
		std::vector<VkSemaphore>	imageAvailableSemaphores;
		std::vector<VkSemaphore>	renderFinishedSemaphores;
		std::vector<VkFence>		inFlightFences;
		bool						framebufferResized = false;
		VkPhysicalDevice			physicalDevice;
		uint32_t					currentFrame = 0;
		VkBuffer					vertexBuffer;
		VkDeviceMemory				vertexBufferMemory;
		VkBuffer					indexBuffer;
		VkDeviceMemory				indexBufferMemory;
		VkDescriptorPool			descriptorPool;
		VkImage						textureImage;
		VkDeviceMemory				textureImageMemory;
		VkImageView					textureImageView;
		VkSampler					textureSampler;
		VkImage						depthImage;
		VkDeviceMemory				depthImageMemory;
		VkImageView					depthImageView;
		std::vector<VkDescriptorSet>descriptorSets;
		std::vector<VkBuffer>		uniformBuffers;
		std::vector<VkDeviceMemory>	uniformBuffersMemory;
		std::vector<void*>			uniformBuffersMapped;

		static std::vector<Vertex>		vertices;
		static std::vector<uint32_t>		indices;
		static const std::vector<const char*>	deviceExtensions;
		static const std::vector<const char*>	validationLayers;
		static const std::size_t MAX_FRAMES_IN_FLIGHT;

		void					initWindow();
		void					initVulkan();
		void					loadModel();
		bool					hasStencilComponent(VkFormat format);
		VkFormat				findDepthFormat();
		VkFormat				findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
		void					createDepthResources();
		void					createTextureSampler();
		VkImageView				createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
		void					createTextureImageView();
		void					copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
		void					transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
		VkCommandBuffer			beginSingleTimeCommands();
		void					endSingleTimeCommands(VkCommandBuffer commandBuffer);
		void					createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
		void					createTextureImage();
		void					createSyncObjects();
		void					createDescriptorPool();
		void					createDescriptorSets();
		void					updateUniformBuffer(uint32_t currentImage);
		void					createUniformBuffers();
		void					createDescriptorSetLayout();
		void					createInstance();
		void					createVertexBuffer();
		void					createIndexBuffer();
		void					createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		void					copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
		void					createCommandBuffer();
		void					cleanupSwapChain();
		void					createCommandPool();
		void					createFramebuffers();
		void					recreateSwapChain();
		uint32_t				findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
		void					recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
		void					createRenderPass();
		void					pickPhysicalDevice();
		QueueFamilyIndices		findQueueFamilies(VkPhysicalDevice physicalDevice);
		void					createLogicalDevice();
		bool					isDeviceSuitable(VkPhysicalDevice device);
		bool					checkDeviceExtensionSupport(VkPhysicalDevice device);
		SwapChainSupportDetails	querySwapChainSupport(VkPhysicalDevice device);
		VkSurfaceFormatKHR		chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR		chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D				chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		void					createSwapChain();
		void					createImageViews();
		void					createSurface();
		void					createGraphicsPipeline();
		VkShaderModule			createShaderModule(const std::vector<char>& code);
		bool					checkValidationLayerSupport();
		void					mainLoop();
		void					drawFrame();
		void					cleanup();

		static void				framebufferResizeCallback(GLFWwindow* window, int width, int height);
		
		public:
		void				run();
	};
	
	std::vector<char>	readFile(const std::string& filename);