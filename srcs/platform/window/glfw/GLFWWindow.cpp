#include "GLFWWindow.hpp"

using namespace platform::window::glfw;

GLFWWindow::GLFWWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	window = glfwCreateWindow(winWidth, winHeight, app::appName, nullptr, nullptr);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

void	GLFWWindow::framebufferResizeCallback(GLFWwindow* rawWindow, int width, int height) {
	auto window = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(rawWindow));
	window->m_wasResized = true;
	(void)width;
	(void)height;
}

uint32_t	GLFWWindow::getWidth() const {
	int width;
	glfwGetFramebufferSize(window, &width, nullptr);
	return static_cast<uint32_t>(width);
}

uint32_t	GLFWWindow::getHeight() const {
	int height;
	glfwGetFramebufferSize(window, nullptr, &height);
	return static_cast<uint32_t>(height);
}

void	GLFWWindow::waitUntilNotMinimized() {
	int width = 0, height = 0;

	glfwGetFramebufferSize(window, &width, &height);

	while (width == 0 || height == 0) {
		glfwGetFramebufferSize(window, &width, &height);
		glfwWaitEvents();
	}

	m_wasResized = false;
}

void	GLFWWindow::getFramebufferSize(uint32_t* width, uint32_t* height) const {
	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	*width = static_cast<uint32_t>(w);
	*height = static_cast<uint32_t>(h);
}

bool	GLFWWindow::shouldClose() const {
	return glfwWindowShouldClose(window);
}

void	GLFWWindow::pollEvents() {
	glfwPollEvents();
}

bool GLFWWindow::wasResized() const {
	return m_wasResized;
}

void*	GLFWWindow::getHandle() const {
	return window;
}

double	GLFWWindow::getTime() const {
	return glfwGetTime();
}

const char**	GLFWWindow::getExtensions(uint32_t* count) const {
	return glfwGetRequiredInstanceExtensions(count);
}

float	GLFWWindow::getAspectRatio() const {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	return static_cast<float>(width) / static_cast<float>(height);
}

GLFWWindow::~GLFWWindow() {
	glfwDestroyWindow(window);
	glfwTerminate();
}
