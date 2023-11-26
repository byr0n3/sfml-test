#ifndef BYRONE_TILE
#define BYRONE_TILE

#define TILE_TOP_LEFT_IDX 6
#define TILE_CENTER_IDX 14
#define TILE_TOP_RIGHT_IDX 12

#include "../core/entity.h"

namespace byrone {
	class Tile : public Entity {
	public:
		Tile();

		explicit Tile(TextureSheet *textureSheet, int spriteIdx, sf::Vector2f position);
	};
}

#endif
