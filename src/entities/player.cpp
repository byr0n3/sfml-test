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

	this->animations = byrone::AnimationController();
	this->animations.add(byrone::Animation(0.5f, 3, 4));
	this->animations.add(byrone::Animation(0.5f, 0, 1));
	this->animations.add(byrone::Animation(0.1f, 12, 17));
	this->animations.add(byrone::Animation(0.1f, 6, 11));
}

void byrone::Player::handleInput(const float &deltaTime) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->velocity.x -= PLAYER_MOVE_SPEED;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->velocity.x += PLAYER_MOVE_SPEED;
	}

	// @todo Only on key down, not hold
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
		byrone::Flags::has<byrone::PlayerFlags, byrone::PlayerFlags::Grounded>(this->flags)) {
		this->velocity.y -= PLAYER_JUMP_VELOCITY;
	}
}

void byrone::Player::update(const float &deltaTime, std::vector<byrone::Tile> *tiles) {
	if (this->velocity.x < 0) {
		byrone::Flags::add<byrone::PlayerFlags, byrone::PlayerFlags::Flipped>(this->flags);
	} else if (this->velocity.x > 0) {
		byrone::Flags::remove<byrone::PlayerFlags, byrone::PlayerFlags::Flipped>(this->flags);
	}

	this->updateAnimation();

	this->animations.update(deltaTime);
	this->updateSprite(this->animations.getCurrentFrame());

	if (!byrone::Flags::has<byrone::PlayerFlags, byrone::PlayerFlags::Grounded>(this->flags)) {
		// @todo (PLAYER_GRAVITY_ACCEL * deltaTime) because gravity
		this->velocity.y += PLAYER_GRAVITY_ACCEL;

		if (this->velocity.y >= PLAYER_GRAVITY_MAX) {
			this->velocity.y = PLAYER_GRAVITY_MAX;
		}
	}

	if (this->velocity == VECTOR2F_ZERO) {
		return;
	}

	sf::Vector2i size = this->getSize();

	sf::Vector2f targetPosition = this->getPosition() + (this->velocity * deltaTime);
	this->velocity.x = 0.0f;

	sf::FloatRect playerRect(targetPosition.x, targetPosition.y, size.x, size.y);

	byrone::Flags::remove<byrone::PlayerFlags, byrone::PlayerFlags::Grounded>(this->flags);

	for (const byrone::Tile &tile: *tiles) {
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

			this->velocity.y = 0.0f;
		}

		// if the target position is in a tile, don't move
		if (tile.getGlobalBounds().intersects(playerRect)) {
			return;
		}
	}

	this->setPosition(targetPosition);
}

void byrone::Player::updateAnimation() {
	if (this->velocity.x == 0) {
		bool flipped = byrone::Flags::has<byrone::PlayerFlags, byrone::PlayerFlags::Flipped>(this->flags);

		this->animations.set(flipped ? 0 : 1);

		return;
	}

	this->animations.set(this->velocity.x < 0 ? 2 : 3);
}
