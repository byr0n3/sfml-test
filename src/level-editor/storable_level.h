#ifndef BYRONE_STORABLE_LEVEL
#define BYRONE_STORABLE_LEVEL

#include "storable_tile.h"
#include <vector>

namespace byrone {
	class StorableLevel {
	public:
		StorableLevel();

		StorableLevel(const char *tileSetPath, const int &tileSize);

		void addOrReplaceTile(const int &textureId, const sf::Vector2f &position);

		bool removeTile(const int &index);

		bool removeTile(const sf::Vector2f &position);

		int getTileAtPosition(const sf::Vector2f &position);

		[[nodiscard]] const char *getTileSetPath() const;

		[[nodiscard]] int getTileSize() const;

		std::vector<byrone::StorableTile> *getTiles();

		bool write(const char *path);

		static StorableLevel readFromFile(const char *path);

	private:
		const char *tileSetPath;
		const int tileSize;
		std::vector<byrone::StorableTile> tiles;
	};
}

#endif
