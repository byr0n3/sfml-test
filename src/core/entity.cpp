#include "entity.h"

byrone::Entity::Entity() = default;

byrone::Entity::Entity(byrone::TextureSheet *textureSheet,
					   sf::Vector2f position,
					   float rotation,
					   sf::Vector2f scale,
					   sf::Color color) : textureSheet(textureSheet), color(color) {
	this->setPosition(position);
	this->setRotation(rotation);
	this->setScale(scale);
	this->setColor(color);
}

void byrone::Entity::updateSprite(int index) {
	this->setTexture(*this->textureSheet->getTexture());
	this->setTextureRect(this->textureSheet->get(index));
}


void byrone::Entity::updateSprite(int x, int y, int width, int height) {
	this->setTexture(*this->textureSheet->getTexture());
	this->setTextureRect(this->textureSheet->get(x, y, width, height));
}
