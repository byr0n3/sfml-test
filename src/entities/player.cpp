#include "player.h"
#include "../exceptions/texture_load_exception.h"
#include <SFML/Window/Keyboard.hpp>

#define TEXTURE_TILE_SIZE sf::Vector2i(16, 16)
#define TEXTURE_PATH "../assets/textures/player.png"

byrone::Player::Player(sf::Vector2f position) {
	this->textureSheet = new byrone::TextureSheet(TEXTURE_PATH, TEXTURE_TILE_SIZE);
	this->updateSprite(0);
	this->setPosition(position);

	// 16 * 2 = 32
	this->setScale(2.0f, 2.0f);
}

void byrone::Player::handleInput() {
	// @todo TEMP REMOVE
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->input.y -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->input.y += 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->input.x -= 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->input.x += 1;
	}
}

// @todo Jumping
// @todo Gravity
// @todo Grounded check
void byrone::Player::update(const float &deltaTime, std::vector<byrone::Tile> *tiles) {
	if (this->input == VECTOR2I_ZERO) {
		return;
	}

	sf::Vector2i size = this->getSize();
	sf::Vector2f movement = {(float) this->input.x * PLAYER_MOVE_SPEED, (float) this->input.y * PLAYER_MOVE_SPEED};

	sf::Vector2f targetPosition = this->getPosition() + (movement * deltaTime);
	this->input = VECTOR2I_ZERO;

	sf::FloatRect playerRect(targetPosition.x, targetPosition.y, size.x, size.y);

	for (const auto &tile: *tiles) {
		sf::Vector2f diff = tile.getPosition() - targetPosition;

		// don't check tiles that are out of range
		if ((diff.x < -size.x || diff.x > size.x) ||
			(diff.y < -size.y || diff.y > size.y)) {
			continue;
		}

		auto bounds = tile.getGlobalBounds();

		// if the target position is in a tile, don't move
		if (bounds.intersects(playerRect)) {
			return;
		}
	}

	this->setPosition(targetPosition);
}
