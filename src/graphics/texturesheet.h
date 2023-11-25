#ifndef BYRONE_TEXTURESHEET
#define BYRONE_TEXTURESHEET

#include <SFML/Graphics/Texture.hpp>

namespace byrone {
	class TextureSheet {
	public:
		TextureSheet();

		TextureSheet(const sf::Texture &texture, sf::Vector2i size);

		sf::Texture *getTexture();

		[[nodiscard]] sf::IntRect get(int index) const;

		[[nodiscard]] sf::IntRect get(int x, int y, int width = 0, int height = 0) const;

		[[nodiscard]] sf::Vector2i getSize() const;

	private:
		sf::Texture texture;
		sf::Vector2i size;
	};
}

#endif
