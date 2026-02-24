#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define VK_USE_PLATFORM_WIN32_KHR
#ifdef _WIN32
# define GLFW_EXPOSE_NATIVE_WIN32
# include <GLFW/glfw3native.h>
#endif

#include "../IWindow.hpp"
#include "../app/ApplicationInfo.hpp"

namespace platform::window::glfw {
class GLFWWindow : public platform::window::IWindow {
private:
	GLFWwindow*	window;
	bool		m_wasResized = false;

	static void	framebufferResizeCallback(GLFWwindow* rawWindow, int width, int height);

public:
	GLFWWindow();
	~GLFWWindow() override;

	uint32_t		getWidth() const override;
	uint32_t		getHeight() const override;
	void			getFramebufferSize(uint32_t* width, uint32_t* height) const override;
	float			getAspectRatio() const override;
	void			waitUntilNotMinimized() override;
	bool			shouldClose() const override;
	void			pollEvents() override;
	bool			wasResized() const override;
	void*			getHandle() const override;
	const char**	getExtensions(uint32_t* count) const override;
	double			getTime() const override;
};
}
