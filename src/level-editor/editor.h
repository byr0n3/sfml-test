#ifndef BYRONE_LEVEL_EDITOR
#define BYRONE_LEVEL_EDITOR

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include "../entities/tile.h"
#include "storable_tile.h"

namespace byrone {
	class LevelEditor {
	public:
		LevelEditor();

		explicit LevelEditor(const char *tileSetPath, int tileSize);

		void handleInput(const float &mouseScrollDelta);

		void update(sf::RenderWindow *window, const float &deltaTime);

		void draw(sf::RenderWindow *window);

		[[nodiscard]] sf::Vector2i getTileSize() const;

		[[nodiscard]] sf::Vector2f getTileSizeF() const;

	private:
		byrone::TextureSheet tileSet;

		byrone::Tile currentTile;
		std::vector<byrone::StorableTile> tiles;

		int getTileIdx();

		void removeTile();
	};
}

#endif
