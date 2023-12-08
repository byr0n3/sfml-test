#include "input_manager.h"

#define MOUSE_OFFSET (int)sf::Keyboard::KeyCount

byrone::InputKey::InputKey() = default;

byrone::InputManager *byrone::InputManager::instance = nullptr;

byrone::InputManager *byrone::InputManager::Instance() {
	if (instance == nullptr) {
		instance = new byrone::InputManager;
	}

	return instance;
}

byrone::InputManager::InputManager() = default;

bool byrone::InputManager::isKeyDown(const sf::Keyboard::Key &code) {
	if (!this->hasKey(code)) {
		return false;
	}

	return byrone::InputManager::inputs[code].current;
}

bool byrone::InputManager::isKeyUp(const sf::Keyboard::Key &code) {
	if (!this->hasKey(code)) {
		return false;
	}

	return !byrone::InputManager::inputs[code].current;
}

bool byrone::InputManager::isKeyPressed(const sf::Keyboard::Key &code) {
	if (!this->hasKey(code)) {
		return false;
	}

	byrone::InputKey key = byrone::InputManager::inputs[code];

	return !key.previous && key.current;
}

bool byrone::InputManager::isKeyReleased(const sf::Keyboard::Key &code) {
	if (!this->hasKey(code)) {
		return false;
	}

	byrone::InputKey key = byrone::InputManager::inputs[code];

	return key.previous && !key.current;
}

bool byrone::InputManager::isMouseDown(const sf::Mouse::Button &button) {
	if (!this->hasKey(MOUSE_OFFSET + button)) {
		return false;
	}

	return byrone::InputManager::inputs[MOUSE_OFFSET + button].current;
}

bool byrone::InputManager::isMouseUp(const sf::Mouse::Button &button) {
	if (!this->hasKey(MOUSE_OFFSET + button)) {
		return false;
	}

	return !byrone::InputManager::inputs[MOUSE_OFFSET + button].current;
}

bool byrone::InputManager::isMousePressed(const sf::Mouse::Button &button) {
	if (!this->hasKey(MOUSE_OFFSET + button)) {
		return false;
	}

	byrone::InputKey key = byrone::InputManager::inputs[MOUSE_OFFSET + button];

	return !key.previous && key.current;
}

bool byrone::InputManager::isMouseReleased(const sf::Mouse::Button &button) {
	if (!this->hasKey(MOUSE_OFFSET + button)) {
		return false;
	}

	byrone::InputKey key = byrone::InputManager::inputs[MOUSE_OFFSET + button];

	return key.previous && !key.current;
}

float byrone::InputManager::getMouseDelta() const {
	return this->mouseDelta;
}

// Make sure this function is called LAST in the event loop
void byrone::InputManager::handleEvent(const sf::Event *event) {
	if (event->type == sf::Event::MouseWheelScrolled) {
		this->mouseDelta = event->mouseWheelScroll.delta;
	}

	if (event->type == sf::Event::MouseButtonReleased || event->type == sf::Event::MouseButtonPressed) {
		for (int i = MOUSE_OFFSET; i < (MOUSE_OFFSET + sf::Mouse::ButtonCount); i++) {
			if (i == MOUSE_OFFSET + event->mouseButton.button) {
				byrone::InputManager::inputs[i].current = event->type != sf::Event::MouseButtonReleased;
			}
		}
	}

	if (event->type == sf::Event::KeyReleased || event->type == sf::Event::KeyPressed) {
		for (int i = 0; i < MOUSE_OFFSET; i++) {
			if (i == event->key.code) {
				byrone::InputManager::inputs[i].current = event->type != sf::Event::KeyReleased;
			}
		}
	}
}

// This should be the LAST function called in the game loop
void byrone::InputManager::update() {
	for (auto k: byrone::InputManager::inputs) {
		byrone::InputManager::inputs[k.first].previous = k.second.current;
	}

	this->mouseDelta = 0.0f;
}

bool byrone::InputManager::hasKey(const int &key) const {
	return this->inputs.find(key) != this->inputs.end();
}
