#include "editor.h"
#include "../exceptions/load_file_exception.h"
#include "../core/utilities.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>

int spriteIdx = 0;
sf::Vector2f placePosition;

void updatePlacePosition(const sf::RenderWindow &window, float tileSize) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	float x = std::floor((float) mousePosition.x / tileSize);
	float y = std::floor((float) mousePosition.y / tileSize);

	placePosition = sf::Vector2f(x, y) * tileSize;
}

byrone::LevelEditor::LevelEditor() = default;

byrone::LevelEditor::LevelEditor(const char *tileSetPath, int tileSize) {
	this->tileSet = byrone::TextureSheet(tileSetPath, {tileSize, tileSize});

	this->currentTile = byrone::Tile(&this->tileSet, spriteIdx, VECTOR2F_ZERO);
}

void byrone::LevelEditor::update(const sf::RenderWindow &window, const float &mouseScrollDelta) {
	updatePlacePosition(window, this->getTileSizeF().x);

	this->currentTile.setPosition(placePosition);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		// @todo Replace tile if different sprite index
		if (this->canPlaceTile()) {
			this->currentTile.setColor(sf::Color::White);
			this->tiles.push_back(this->currentTile);
		}
	}

	this->currentTile.setColor(sf::Color(255, 255, 255, 150));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		this->removeTile();
	}

	if (mouseScrollDelta > 0) {
		this->currentTile.setTextureRect(this->tileSet.get(++spriteIdx));
	} else if (mouseScrollDelta < 0) {
		this->currentTile.setTextureRect(this->tileSet.get(--spriteIdx));
	}
}

void byrone::LevelEditor::draw(sf::RenderWindow *window) {
	window->clear(sf::Color::Blue);

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
		return tile.getPosition() != placePosition;
	});
}

void byrone::LevelEditor::removeTile() {
	int idx = -1;

	for (int i = 0; i < this->tiles.size(); i++) {
		if (this->tiles[i].getPosition() == placePosition) {
			idx = i;
			break;
		}
	}

	if (idx == -1) {
		return;
	}

	// @todo Deconstruct?
	this->tiles.erase(this->tiles.begin() + idx);
}
