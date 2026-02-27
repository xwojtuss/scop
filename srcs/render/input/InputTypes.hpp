#pragma once

#include <cstdint>
#include <unordered_map>
#include <functional>
#include <glm/glm.hpp>

namespace render::input {
typedef int	InputEvents;
enum InputEvent {
	MoveForward = 1 << 0,
	MoveBackward = 1 << 1,
	MoveRight = 1 << 2,
	MoveLeft = 1 << 3,
	Jump = 1 << 4,
	Crouch = 1 << 5,
	AnyMove = MoveForward | MoveBackward | MoveRight | MoveLeft | Jump | Crouch,
	ToggleCursor = 1 << 6,
	ActionButton = 1 << 7,
	SecondaryButton = 1 << 8,
	AnyMouseButton = ActionButton | SecondaryButton,
	All = 1 << (sizeof(InputEvents) * 8 - 1)
};

enum MouseButton {
	LeftButton = 1 << 0,
	RightButton = 1 << 1,
	MiddleButton = 1 << 2,
	Button4 = 1 << 3,
	Button5 = 1 << 4,
	Button6 = 1 << 5,
	Button7 = 1 << 6,
	Button8 = 1 << 7,
	AnyButton = LeftButton | RightButton | MiddleButton | Button4 | Button5 | Button6 | Button7 | Button8
};

struct InputCommand {
	float		moveForward;
	float		moveRight;
	float		moveUp;
	float		lookUp;
	float		lookRight;
	InputEvents	startedEvents;
	InputEvents	repeatedEvents;
	InputEvents	releasedEvents;
	InputEvents	activeEvents;

	float		maxPitch = glm::radians(89.0f);
};

enum InputAction {
	Press,
	Release,
	Repeat
};

typedef int	InputMods;
enum InputMod {
	Shift = 1 << 0,
	Control = 1 << 1,
	Alt = 1 << 2,
	Super = 1 << 3
};

constexpr bool	hasModifier(InputMods mods, InputMod mod) {
	return (mods & mod) != 0;
}

constexpr bool	hasEvent(InputEvents events, InputEvent event) {
	return (events & event) != 0;
}

constexpr bool	hasAnyEvent(InputEvents events, InputEvents other) {
	return (events & other) != 0;
}

constexpr bool	hasAllEvents(InputEvents events, InputEvents other) {
	return (events & other) == other;
}

typedef long	Input;

constexpr Input	createInput(int scancode, InputMods mods) {
	return (scancode << 8) | mods;
}

constexpr Input	createMouseInput(MouseButton button, InputMods mods) {
	return (button << 16) | mods;
}

constexpr int	getScancode(Input input) {
	return input >> 8;
}

constexpr MouseButton	getMouseButton(Input input) {
	return static_cast<MouseButton>(input >> 16);
}

typedef std::unordered_map<Input, InputEvent>	InputEventBindings;

}