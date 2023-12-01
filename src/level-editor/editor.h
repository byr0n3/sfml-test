#ifndef BYRONE_LEVEL_EDITOR
#define BYRONE_LEVEL_EDITOR

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include "../entities/tile.h"

namespace byrone {
	class LevelEditor {
	public:
		LevelEditor();

		explicit LevelEditor(const char *tileSetPath, int tileSize);

		void update(const sf::RenderWindow &window, const float &mouseScrollDelta);

		void draw(sf::RenderWindow *window);

		[[nodiscard]] sf::Vector2i getTileSize() const;

		[[nodiscard]] sf::Vector2f getTileSizeF() const;

	private:
		byrone::TextureSheet tileSet;

		byrone::Tile currentTile;
		std::vector<byrone::Tile> tiles;

		bool canPlaceTile();

		void removeTile();
	};
}

#endif
