#pragma once

#include <cstdint>
#include <unordered_map>
#include <functional>

namespace render::input {
typedef int	InputEvents;
enum InputEvent {
	MoveForward = 1 << 0,
	MoveBackward = 1 << 1,
	MoveRight = 1 << 2,
	MoveLeft = 1 << 3,
	Jump = 1 << 4,
	Crouch = 1 << 5,
	AnyMove = MoveForward | MoveBackward | MoveRight | MoveLeft | Jump | Crouch
};

struct InputCommand {
	float		moveForward;
	float		moveRight;
	float		moveUp;
	float		lookUp;
	float		lookRight;
	InputEvents	startedEvents;
	InputEvents	repeatedEvents;
	InputEvents	stoppedEvents;
	InputEvents	activeEvents;
	float		maxPitch;
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

typedef int	Input;

constexpr Input	createInput(int scancode, InputMods mods) {
	return (scancode << 8) | mods;
}

constexpr int	getScancode(Input input) {
	return input >> 8;
}

typedef std::unordered_map<Input, InputEvent>	InputEventBindings;

}