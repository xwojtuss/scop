#pragma once

#include <cstdint>

namespace render::input {
struct InputCommand {
	float		moveForward;
	float		moveRight;
	float		lookUp;
	float		lookRight;
	uint32_t	eventBits;
};

enum InputActions {
	Press,
	Release,
	Repeat
};

enum InputMods {
	Shift = 1 << 0,
	Control = 1 << 1,
	Alt = 1 << 2,
	Super = 1 << 3
};

enum PlayerEvents {
	JUMP = 1 << 0,
	CROUCH = 1 << 1
};
}