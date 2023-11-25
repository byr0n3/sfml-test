#ifndef BYRONE_PLAYER
#define BYRONE_PLAYER

#include "core/entity.h"
#include "core/utilities.h"

namespace byrone {
	class Player : public Entity {
	public:
		explicit Player(sf::Vector2f position = VECTOR2F_ZERO);

		sf::Vector2i getSize() const;

		void handleInput() override;

		void update(float deltaTime) override;

	private:
		sf::Vector2f input;
	};
}

#endif
