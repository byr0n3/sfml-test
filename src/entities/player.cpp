#include "player.h"
#include "../exceptions/texture_load_exception.h"
#include "../core/flags.h"
#include <SFML/Window/Keyboard.hpp>

#define TEXTURE_TILE_SIZE sf::Vector2i(16, 16)
#define TEXTURE_PATH "../assets/textures/player.png"

byrone::Player::Player(sf::Vector2f position) : flags(byrone::PlayerFlags::None) {
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
void byrone::Player::update(const float &deltaTime, std::vector<byrone::Tile> *tiles) {
	if (this->input == VECTOR2I_ZERO) {
		return;
	}

	sf::Vector2i size = this->getSize();
	sf::Vector2f movement = {(float) this->input.x * PLAYER_MOVE_SPEED, (float) this->input.y * PLAYER_MOVE_SPEED};

	sf::Vector2f targetPosition = this->getPosition() + (movement * deltaTime);
	this->input = VECTOR2I_ZERO;

	sf::FloatRect playerRect(targetPosition.x, targetPosition.y, size.x, size.y);

	byrone::Flags::remove<byrone::PlayerFlags, byrone::PlayerFlags::Grounded>(this->flags);

	for (const auto &tile: *tiles) {
		sf::Vector2f diff = tile.getPosition() - targetPosition;

		int diffX = (int) diff.x;
		int diffY = (int) diff.y;

		// don't check tiles that are out of range
		if ((diffX < -size.x || diffX > size.x) ||
			(diffY < -size.y || diffY > size.y)) {
			continue;
		}

		if ((diffX >= -size.x && diffX <= size.x) &&
			(diffY >= -size.y && diffY <= size.y)) {
			byrone::Flags::add<byrone::PlayerFlags, byrone::PlayerFlags::Grounded>(this->flags);
		}

		// if the target position is in a tile, don't move
		if (tile.getGlobalBounds().intersects(playerRect)) {
			return;
		}
	}

	this->setPosition(targetPosition);
}
