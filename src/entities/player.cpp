#include "player.h"
#include "../exceptions/texture_load_exception.h"
#include "../core/flags.h"
#include <SFML/Window/Keyboard.hpp>

#define TEXTURE_TILE_SIZE sf::Vector2i(16, 16)
#define TEXTURE_PATH "../assets/textures/player.png"
#define TEXTURE_SCALE 2.0f

byrone::Player::Player(sf::Vector2f position) : flags(byrone::PlayerFlags::None) {
	this->textureSheet = new byrone::TextureSheet(TEXTURE_PATH, TEXTURE_TILE_SIZE);
	this->updateSprite(0);
	this->setPosition(position);

	// 16 * 2 = 32
	this->setScale(TEXTURE_SCALE, TEXTURE_SCALE);

	this->idleLeftAnimation = byrone::Animation(0.5f, 3, 4);
	this->idleRightAnimation = byrone::Animation(0.5f, 0, 1);
	this->walkLeftAnimation = byrone::Animation(0.1f, 12, 17);
	this->walkRightAnimation = byrone::Animation(0.1f, 6, 11);
}

void byrone::Player::handleInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->input.x -= 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->input.x += 1;
	}

	// @todo Only on key down, not hold
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		this->input.y -= 1;
	}
}

// @todo Jumping
// @todo Gravity
void byrone::Player::update(const float &deltaTime, std::vector<byrone::Tile> *tiles) {
	if (this->input.x != 0) {
		if (this->input.x > 0) {
			byrone::Flags::remove<byrone::PlayerFlags, byrone::PlayerFlags::Flipped>(this->flags);

			this->walkRightAnimation.update(deltaTime);

			this->updateSprite(this->walkRightAnimation.getCurrentFrame());
		} else {
			byrone::Flags::add<byrone::PlayerFlags, byrone::PlayerFlags::Flipped>(this->flags);

			this->walkLeftAnimation.update(deltaTime);

			this->updateSprite(this->walkLeftAnimation.getCurrentFrame());
		}
	} else {
		if (byrone::Flags::has<byrone::PlayerFlags, byrone::PlayerFlags::Flipped>(this->flags)) {
			this->idleLeftAnimation.update(deltaTime);

			this->updateSprite(this->idleLeftAnimation.getCurrentFrame());
		} else {
			this->idleRightAnimation.update(deltaTime);

			this->updateSprite(this->idleRightAnimation.getCurrentFrame());
		}
	}

	if (!byrone::Flags::has<byrone::PlayerFlags, byrone::PlayerFlags::Grounded>(this->flags) && this->input.y == 0) {
		this->input.y = 1;
	}

	if (this->input == VECTOR2I_ZERO) {
		return;
	}

	sf::Vector2i size = this->getSize();
	sf::Vector2f movement = {(float) this->input.x * PLAYER_MOVE_SPEED,
	                         (float) this->input.y * (this->input.y < 0 ? PLAYER_GRAVITY * 0.9f : PLAYER_GRAVITY)};

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
