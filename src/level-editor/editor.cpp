#include "editor.h"
#include "../exceptions/load_file_exception.h"
#include "../core/utilities.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Mouse.hpp>

sf::Vector2f getPlacePosition(const sf::RenderWindow &window, float tileSize) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	float x = std::floor((float) mousePosition.x / tileSize);
	float y = std::floor((float) mousePosition.y / tileSize);

	return sf::Vector2f(x, y) * tileSize;
}

byrone::LevelEditor::LevelEditor() = default;

byrone::LevelEditor::LevelEditor(const char *tileSetPath, int tileSize) {
	this->tileSet = byrone::TextureSheet(tileSetPath, {tileSize, tileSize});

	if (!this->font.loadFromFile("../assets/fonts/mono.ttf")) {
		throw byrone::load_file_exception("../assets/fonts/mono.ttf");
	}

	this->currentTile = byrone::Tile(&this->tileSet, 0, VECTOR2F_ZERO);
}

void byrone::LevelEditor::update(const sf::RenderWindow &window) {
	this->placePosition = getPlacePosition(window, this->getTileSizeF().x);
	this->currentTile.setPosition(this->placePosition);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->canPlaceTile()) {
		this->tiles.push_back(this->currentTile);
	}
}

void byrone::LevelEditor::draw(sf::RenderWindow *window) {
	window->clear(sf::Color::Blue);

	std::string label =
			"Position: " + std::to_string((int) placePosition.x) + "," + std::to_string((int) placePosition.y);

	sf::Text text(label, font, 24);

	text.setPosition(10.0f, 10.0f);

	text.setFillColor(sf::Color::White);

	window->draw(text);

	window->draw(currentTile);

	for (const byrone::Tile &tile: tiles) {
		window->draw(tile);
	}
}

sf::Vector2i byrone::LevelEditor::getTileSize() const {
	return this->tileSet.getSize();
}

sf::Vector2f byrone::LevelEditor::getTileSizeF() const {
	return (sf::Vector2f) this->tileSet.getSize();
}

bool byrone::LevelEditor::canPlaceTile() {
	return std::all_of(this->tiles.cbegin(), this->tiles.cend(), [this](const byrone::Tile &tile) {
		return tile.getPosition() != this->placePosition;
	});
}
