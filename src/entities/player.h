#ifndef BYRONE_PLAYER
#define BYRONE_PLAYER

#define PLAYER_MOVE_SPEED 100.0f

#include "../core/entity.h"
#include "../core/utilities.h"
#include "tile.h"

namespace byrone {
	class Player : public Entity {
	public:
		explicit Player(sf::Vector2f position = VECTOR2F_ZERO);

		void handleInput() override;

		void update(const float &deltaTime, std::vector<Tile> *tiles);

	private:
		sf::Vector2i input;
	};
}

#endif
