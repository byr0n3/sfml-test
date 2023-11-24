#include "spritesheet.h"
#include <iostream>

byrone::Spritesheet::Spritesheet() = default;

byrone::Spritesheet::~Spritesheet() {
	std::cout << "Spritesheet deconstructor called." << std::endl;
}

byrone::Spritesheet::Spritesheet(const sf::Texture &texture,
								 sf::Vector2i size,
								 sf::Vector2i padding) : texture(texture), size(size), padding(padding) {
}

sf::Texture byrone::Spritesheet::getTexture() const {
	return this->texture;
}

sf::IntRect byrone::Spritesheet::get(int x, int y, int width, int height) const {
	if (width <= 0) {
		width = this->size.x;
	}

	if (height <= 0) {
		height = this->size.y;
	}

	return {
			this->padding.x + x,
			this->padding.y + y,
			width,
			height
	};
}

sf::Vector2i byrone::Spritesheet::getSize() const {
	return this->size;
}
