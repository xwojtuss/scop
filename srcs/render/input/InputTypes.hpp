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

enum PlayerEvents {
	JUMP = 1 << 0,
	CROUCH = 1 << 1
};
}