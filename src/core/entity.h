#ifndef BYRONE_ENTITY
#define BYRONE_ENTITY

#include "spritesheet.h"
#include <SFML/Graphics/Sprite.hpp>

namespace byrone {
	class Entity : public sf::Sprite {
	public:
		Entity();

		explicit Entity(byrone::Spritesheet *spritesheet,
						sf::Vector2f position = sf::Vector2f(0.0f, 0.0f),
						float rotation = 0.0f,
						sf::Vector2f scale = sf::Vector2f(1.0f, 1.0f),
						sf::Color color = sf::Color::White);

		void updateSprite(int x, int y, int width = 0, int height = 0);

	private:
		sf::Color color;
		std::shared_ptr<byrone::Spritesheet> spritesheet;
	};
}


#endif
