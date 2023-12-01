#ifndef BYRONE_TILE
#define BYRONE_TILE

#include "../core/entity.h"

namespace byrone {
	class Tile : public Entity {
	public:
		Tile();

		explicit Tile(TextureSheet *textureSheet, int spriteIdx, sf::Vector2f position);
	};
}

#endif
