#include "tile.h"

byrone::Tile::Tile() = default;

byrone::Tile::Tile(byrone::TextureSheet *textureSheet, sf::Vector2f position) {
	this->textureSheet = textureSheet;
	this->setPosition(position);
	this->setScale(2.0f, 2.0f);

	this->updateSprite(0);
}
