#ifndef BYRONE_PLAYER
#define BYRONE_PLAYER

#define PLAYER_MOVE_SPEED 100.0f
#define PLAYER_GRAVITY 100.0f

#include <cstdint>
#include "../core/entity.h"
#include "../core/utilities.h"
#include "tile.h"
#include "../graphics/animation_controller.h"

namespace byrone {
	enum PlayerFlags : int16_t {
		None = 0,
		Flipped = (1 << 0),
		Grounded = (1 << 1),
	};

	class Player : public Entity {
	public:
		explicit Player(sf::Vector2f position = VECTOR2F_ZERO);

		void handleInput() override;

		void update(const float &deltaTime, std::vector<Tile> *tiles);

	private:
		PlayerFlags flags;
		AnimationController animations;
		sf::Vector2i input;

		void updateAnimation();
	};
}

#endif
