#include "storable_tile.h"

byrone::StorableTile::StorableTile() = default;

byrone::StorableTile::StorableTile(const int &textureIdx, const sf::Vector2f &position) : textureIdx(textureIdx),
																						  position(position) {
}

void byrone::StorableTile::setTextureIdx(const int &newTextureIdx) {
	this->textureIdx = newTextureIdx;
}

int byrone::StorableTile::getTextureIdx() const {
	return this->textureIdx;
}

sf::Vector2f byrone::StorableTile::getPosition() const {
	return this->position;
}
