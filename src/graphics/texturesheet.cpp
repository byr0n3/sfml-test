#include "texturesheet.h"
#include "../exceptions/load_file_exception.h"

byrone::TextureSheet::TextureSheet() = default;

byrone::TextureSheet::TextureSheet(const char *filePath, sf::Vector2i size) : size(size) {
	if (!this->texture.loadFromFile(filePath)) {
		throw load_file_exception(filePath);
	}
}

byrone::TextureSheet::TextureSheet(const sf::Texture &texture, sf::Vector2i size) : texture(texture), size(size) {
}

sf::Texture *byrone::TextureSheet::getTexture() {
	return &this->texture;
}

sf::IntRect byrone::TextureSheet::get(int index) const {
	sf::Vector2 textureSize = this->texture.getSize();
	int width = this->size.x;
	int height = this->size.y;

	int availableX = (int) textureSize.x / width;

	int x = (index % availableX) * width;
	int y = index / availableX * height;

	return this->get(x, y, width, height);
}

sf::IntRect byrone::TextureSheet::get(int x, int y, int width, int height) const {
	if (width <= 0) {
		width = this->size.x;
	}

	if (height <= 0) {
		height = this->size.y;
	}

	return {x, y, width, height};
}

sf::Vector2i byrone::TextureSheet::getSize() const {
	return this->size;
}
