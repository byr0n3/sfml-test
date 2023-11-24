#include "texturesheet.h"

byrone::TextureSheet::TextureSheet() = default;

byrone::TextureSheet::TextureSheet(const sf::Texture &texture,
								   sf::Vector2i size,
								   sf::Vector2i padding) : texture(texture), size(size), padding(padding) {
}

sf::Texture *byrone::TextureSheet::getTexture() {
	return &this->texture;
}

sf::IntRect byrone::TextureSheet::get(int index) const {
	sf::Vector2 textureSize = this->texture.getSize();
	auto width = this->size.x;
	auto height = this->size.y;

	int availableX = (((int) textureSize.x - (this->padding.x * 2)) / width);

	auto x = (index % availableX) * width;
	auto y = index / availableX * height;

	return this->get(x, y, width, height);
}

sf::IntRect byrone::TextureSheet::get(int x, int y, int width, int height) const {
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

sf::Vector2i byrone::TextureSheet::getSize() const {
	return this->size;
}
