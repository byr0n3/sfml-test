#ifndef BYRONE_LEVEL
#define BYRONE_LEVEL

#include <vector>
#include "../entities/tile.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace byrone {
	struct Level {
	public:
		Level();

		explicit Level(const char *path, const float &windowHeight);

		void draw(sf::RenderWindow *window);

		std::vector<Tile> *getTiles();

	private:
		TextureSheet *textureSheet;

		std::vector<Tile> tiles;
	};
}

#endif
