#ifndef BYRONE_LEVEL_EDITOR
#define BYRONE_LEVEL_EDITOR

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include "../entities/tile.h"
#include "storable_tile.h"
#include "storable_level.h"

namespace byrone {
	class LevelEditor {
	public:
		LevelEditor();

		explicit LevelEditor(const char *tileSetPath, int tileSize);

		void handleInput();

		void update(sf::RenderWindow *window, const float &deltaTime);

		void draw(sf::RenderWindow *window);

		[[nodiscard]] sf::Vector2i getTileSize() const;

		[[nodiscard]] sf::Vector2f getTileSizeF() const;

	private:
		byrone::TextureSheet tileSet;
		byrone::StorableLevel level;

		// @todo Don't store and make a new instance each update?
		// Would maybe be allocated on stack, might be faster/less resource heavy
		byrone::Tile currentTile;
	};
}

#endif
