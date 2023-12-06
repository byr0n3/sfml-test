#ifndef BYRONE_PLAYER
#define BYRONE_PLAYER

#define PLAYER_MOVE_SPEED 100.0f
#define PLAYER_GRAVITY_MAX 200.0f
#define PLAYER_GRAVITY_ACCEL (PLAYER_GRAVITY_MAX / 10.0f)
#define PLAYER_JUMP_VELOCITY (PLAYER_GRAVITY_MAX * 2.5f)

#include <cstdint>
#include "tile.h"
#include "../core/entity.h"
#include "../core/utilities.h"
#include "../graphics/animation_controller.h"
#include "../core/level.h"

namespace byrone {
	enum PlayerFlags : int16_t {
		None = 0,
		Flipped = (1 << 0),
		Grounded = (1 << 1),
	};

	class Player : public Entity {
	public:
		explicit Player(sf::Vector2f position = VECTOR2F_ZERO);

		void handleInput(const float &deltaTime) override;

		void update(const float &deltaTime, Level *level);

	private:
		PlayerFlags flags;
		AnimationController animations;
		sf::Vector2f velocity;

		void updateAnimation();
	};
}

#endif
