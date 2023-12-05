#include "editor.h"
#include "../exceptions/load_file_exception.h"
#include "../core/utilities.h"
#include "../core/input_manager.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

#define CAMERA_MOVE_SPEED 100.0f
#define CUSTOM_LEVEL_PATH "../assets/levels/custom.lvl"

// @todo Private fields on editor instance?
int textureIdx = 0;
int maxTextureIdx = 0;
sf::Vector2i cameraMovement = VECTOR2I_ZERO;
sf::Vector2f placePosition = VECTOR2F_ZERO;

void updatePlacePosition(sf::RenderWindow *window, float tileSize) {
	sf::Vector2f pixelPosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	float x = std::floor(pixelPosition.x / tileSize);
	float y = std::floor(pixelPosition.y / tileSize);

	placePosition = sf::Vector2f(x, y) * tileSize;
}

void updateTextureIdx(int mod) {
	int target = textureIdx + mod;

	if (target < 0) {
		target = maxTextureIdx;
	}

	if (target > maxTextureIdx) {
		target = 0;
	}

	textureIdx = target;
}

byrone::LevelEditor::LevelEditor() = default;

byrone::LevelEditor::LevelEditor(const char *tileSetPath, int tileSize) {
	this->level = byrone::StorableLevel::loadFromFileOrDefault(CUSTOM_LEVEL_PATH, tileSetPath, tileSize);

	this->tileSet = byrone::TextureSheet(tileSetPath, {tileSize, tileSize});
	maxTextureIdx = this->tileSet.getMaxIndex();

	this->currentTile = byrone::Tile(&this->tileSet, textureIdx, placePosition);
	this->currentTile.setColor(sf::Color(255, 255, 255, 150));
}

void byrone::LevelEditor::handleInput() {
	// Switching texture
	if (byrone::InputManager::Instance()->isKeyPressed(sf::Keyboard::Right)) {
		updateTextureIdx(1);
	}

	if (byrone::InputManager::Instance()->isKeyPressed(sf::Keyboard::Left)) {
		updateTextureIdx(-1);
	}

	float mouseDelta = byrone::InputManager::Instance()->getMouseDelta();

	if (mouseDelta != 0) {
		updateTextureIdx((int) mouseDelta);
	}

	// Update camera position
	if (byrone::InputManager::Instance()->isKeyDown(sf::Keyboard::W)) {
		cameraMovement.y -= 1;
	}

	if (byrone::InputManager::Instance()->isKeyDown(sf::Keyboard::A)) {
		cameraMovement.x -= 1;
	}

	if (byrone::InputManager::Instance()->isKeyDown(sf::Keyboard::S)) {
		cameraMovement.y += 1;
	}

	if (byrone::InputManager::Instance()->isKeyDown(sf::Keyboard::D)) {
		cameraMovement.x += 1;
	}

	// Saving level to file
	if (byrone::InputManager::Instance()->isKeyPressed(sf::Keyboard::Enter)) {
		this->level.write(CUSTOM_LEVEL_PATH);
	}
}

void byrone::LevelEditor::update(sf::RenderWindow *window, const float &deltaTime) {
	// Move the camera
	if (cameraMovement != VECTOR2I_ZERO) {
		// @todo Snap to grid? Some artifacts on sprites when moving
		sf::View view = window->getView();
		view.move(((sf::Vector2f) cameraMovement) * (CAMERA_MOVE_SPEED * deltaTime));
		window->setView(view);

		cameraMovement = VECTOR2I_ZERO;
	}

	// Update the preview tile
	updatePlacePosition(window, this->getTileSizeF().x);
	this->currentTile.setPosition(placePosition);
	this->currentTile.updateTexture(textureIdx);

	// Place tile logic
	if (byrone::InputManager::Instance()->isMouseDown(sf::Mouse::Left)) {
		this->level.addOrReplaceTile(textureIdx, placePosition);
	}

	// Remove tile logic
	if (byrone::InputManager::Instance()->isMouseDown(sf::Mouse::Right)) {
		this->level.removeTile(placePosition);
	}
}

void byrone::LevelEditor::draw(sf::RenderWindow *window) {
	window->clear(sf::Color::Blue);

	window->draw(this->currentTile);

	// Temporarily update the current tile to prevent making a lot of sprite instances
	for (const byrone::StorableTile &tile: *this->level.getTiles()) {
		if (tile.getPosition() == placePosition && tile.getTextureIdx() != textureIdx) {
			continue;
		}

		this->currentTile.updateTexture(tile.getTextureIdx());
		this->currentTile.setPosition(tile.getPosition());
		this->currentTile.setColor(sf::Color::White);

		window->draw(this->currentTile);
	}

	// Reset the current tile (position is updated in update function)
	this->currentTile.updateTexture(textureIdx);
	this->currentTile.setColor(sf::Color(255, 255, 255, 150));
}

sf::Vector2i byrone::LevelEditor::getTileSize() const {
	return this->tileSet.getSize();
}

sf::Vector2f byrone::LevelEditor::getTileSizeF() const {
	return (sf::Vector2f) this->tileSet.getSize();
}
