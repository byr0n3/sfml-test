#include "tile.h"

byrone::Tile::Tile() = default;

byrone::Tile::Tile(byrone::TextureSheet *textureSheet, int spriteIdx, sf::Vector2f position) {
	this->textureSheet = textureSheet;
	this->updateTexture(spriteIdx);
	this->setPosition(position);
}
