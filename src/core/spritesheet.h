#ifndef BYRONE_SPRITESHEET
#define BYRONE_SPRITESHEET

#include "SFML/Graphics/Texture.hpp"

namespace byrone {
	class Spritesheet {
	public:
		Spritesheet();

		~Spritesheet();

		Spritesheet(const sf::Texture &texture, sf::Vector2i size, sf::Vector2i padding = sf::Vector2i(0, 0));

		sf::Texture getTexture() const;

		[[nodiscard]] sf::IntRect get(int x, int y, int width, int height) const;

		[[nodiscard]] sf::Vector2i getSize() const;

	private:
		sf::Texture texture;
		sf::Vector2i padding;
		sf::Vector2i size;
	};
}

#endif
