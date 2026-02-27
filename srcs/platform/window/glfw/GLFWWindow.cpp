#include "GLFWWindow.hpp"

using namespace platform::window::glfw;

GLFWWindow::GLFWWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	m_window = glfwCreateWindow(winWidth, winHeight, app::appName, nullptr, nullptr);
	glfwSetWindowUserPointer(m_window, this);
	glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);

	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	setMouseCursorVisible(false);
	glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GLFW_FALSE);

	glfwSetCursorPosCallback(m_window, cursorPositionCallback);
	glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
	glfwSetKeyCallback(m_window, keyCallback);

}

void	GLFWWindow::cursorPositionCallback(GLFWwindow* rawWindow, double xpos, double ypos) {
	auto m_window = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(rawWindow));
	
	m_window->getInputManager().processMouseMove(xpos, ypos);
}

void	GLFWWindow::mouseButtonCallback(GLFWwindow* rawWindow, int button, int action, int mods) {
	auto m_window = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(rawWindow));

	(void)mods;
	m_window->getInputManager().processMouseButton(button, platform::input::glfw::glfwToInputAction(action));
}

void	GLFWWindow::keyCallback(GLFWwindow* rawWindow, int key, int scancode, int action, int mods) {
	auto m_window = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(rawWindow));

	(void)key;
	m_window->getInputManager().processKey(scancode, platform::input::glfw::glfwToInputAction(action), platform::input::glfw::glfwToInputMods(mods));
}

void	GLFWWindow::framebufferResizeCallback(GLFWwindow* rawWindow, int width, int height) {
	auto m_window = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(rawWindow));
	m_window->m_wasResized = true;

	(void)width;
	(void)height;
	m_window->setMouseCursorPositionToCenter();
}

uint32_t	GLFWWindow::getWidth() const {
	int width;
	glfwGetFramebufferSize(m_window, &width, nullptr);
	return static_cast<uint32_t>(width);
}

uint32_t	GLFWWindow::getHeight() const {
	int height;
	glfwGetFramebufferSize(m_window, nullptr, &height);
	return static_cast<uint32_t>(height);
}

void	GLFWWindow::waitUntilNotMinimized() {
	int width = 0, height = 0;

	glfwGetFramebufferSize(m_window, &width, &height);

	while (width == 0 || height == 0) {
		glfwGetFramebufferSize(m_window, &width, &height);
		glfwWaitEvents();
	}

	m_wasResized = false;
}

void	GLFWWindow::getFramebufferSize(uint32_t* width, uint32_t* height) const {
	int w, h;
	glfwGetFramebufferSize(m_window, &w, &h);
	*width = static_cast<uint32_t>(w);
	*height = static_cast<uint32_t>(h);
}

bool	GLFWWindow::shouldClose() const {
	return glfwWindowShouldClose(m_window);
}

void	GLFWWindow::pollEvents() {
	glfwPollEvents();
}

bool GLFWWindow::wasResized() const {
	return m_wasResized;
}

void*	GLFWWindow::getHandle() const {
	return m_window;
}

double	GLFWWindow::getTime() const {
	return glfwGetTime();
}

const char**	GLFWWindow::getExtensions(uint32_t* count) const {
	return glfwGetRequiredInstanceExtensions(count);
}

float	GLFWWindow::getAspectRatio() const {
	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height);
	return static_cast<float>(width) / static_cast<float>(height);
}

void	GLFWWindow::setMouseCursorVisible(bool visible) {
	glfwSetInputMode(m_window, GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

void	GLFWWindow::setMouseCursorPosition(double x, double y) {
	glfwSetCursorPos(m_window, x, y);
}

void	GLFWWindow::setMouseCursorPositionToCenter() {
	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height);
	setMouseCursorPosition(width / 2.0, height / 2.0);
}

render::input::InputManager&	GLFWWindow::getInputManager() {
	return m_inputManager;
}

GLFWWindow::~GLFWWindow() {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}
