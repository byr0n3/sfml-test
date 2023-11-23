#include "entity.h"
#include "SFML/Graphics/Sprite.hpp"

byrone::Entity::Entity() = default;

byrone::Entity::Entity(const sf::Texture &texture,
					   sf::Vector2f position,
					   float rotation,
					   sf::Vector2f scale,
					   sf::Color color) : color(color) {
	this->m_texture = texture;
	this->setPosition(position);
	this->setRotation(rotation);
	this->setScale(scale);
}

void byrone::Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	/*states.transform *= getTransform();
	states.texture = &m_texture;

	target.draw(m_vertices, states);*/

	// @todo Don't draw sprite, get vertices and stuff directly (calculate them when a property like position or rotation changes?)
	sf::Sprite sprite(this->m_texture);
	sprite.setPosition(this->getPosition());
	sprite.setRotation(this->getRotation());
	sprite.setScale(this->getScale());
	sprite.setColor(this->color);

	target.draw(sprite);
}
