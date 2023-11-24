#include "entity.h"

byrone::Entity::Entity() = default;

byrone::Entity::Entity(byrone::Spritesheet *spritesheet,
					   sf::Vector2f position,
					   float rotation,
					   sf::Vector2f scale,
					   sf::Color color) : spritesheet(spritesheet), color(color) {
	this->setPosition(position);
	this->setRotation(rotation);
	this->setScale(scale);
	this->setColor(color);
}

void byrone::Entity::updateSprite(int x, int y, int width, int height) {
	this->setTexture(spritesheet->getTexture());
	this->setTextureRect(spritesheet->get(x, y, width, height));
}
