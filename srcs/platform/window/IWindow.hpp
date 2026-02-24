#pragma once

#include <cstdint>

namespace platform::window {

constexpr uint32_t	winWidth = 800;
constexpr uint32_t	winHeight = 600;
constexpr float		aspectRatio = static_cast<float>(winWidth) / static_cast<float>(winHeight);

class IWindow {
public:
	virtual ~IWindow() = default;

	virtual uint32_t		getWidth() const = 0;
	virtual uint32_t		getHeight() const = 0;
	virtual float			getAspectRatio() const = 0;
	virtual void			getFramebufferSize(uint32_t* width, uint32_t* height) const = 0;
	virtual void			waitUntilNotMinimized() = 0;
	virtual bool			shouldClose() const = 0;
	virtual void			pollEvents() = 0;
	virtual bool			wasResized() const = 0;
	virtual void*			getHandle() const = 0;
	virtual const char**	getExtensions(uint32_t* count) const = 0;
	virtual double			getTime() const = 0;
};
}