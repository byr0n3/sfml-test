#include "player.h"
#include "../exceptions/texture_load_exception.h"
#include <SFML/Window/Keyboard.hpp>

#define TEXTURE_PATH "../assets/textures/player.png"

byrone::Player::Player(sf::Vector2f position) {
	this->textureSheet = new byrone::TextureSheet(TEXTURE_PATH, {16, 16});

	this->setPosition(position);
	// 16 * 4 = 64
	this->setScale(4.0f, 4.0f);

	this->updateSprite(0);
}

sf::Vector2i byrone::Player::getSize() const {
	return this->textureSheet->getSize();
}

void byrone::Player::handleInput() {
	// coordinates start in top-left corner so we subtract here
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->input.y -= 100.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->input.x -= 100.0f;
	}

	// coordinates start in top-left corner so we add here
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->input.y += 100.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->input.x += 100.0f;
	}
}

void byrone::Player::update(float deltaTime) {
	if (this->input == VECTOR2F_ZERO) {
		return;
	}

	this->move(this->input * deltaTime);

	this->input = VECTOR2F_ZERO;
}
