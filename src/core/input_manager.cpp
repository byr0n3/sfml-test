#include "input_manager.h"

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
	return byrone::InputManager::inputs[code].current;
}

bool byrone::InputManager::isKeyUp(const sf::Keyboard::Key &code) {
	return !byrone::InputManager::inputs[code].current;
}

bool byrone::InputManager::isKeyPressed(const sf::Keyboard::Key &code) {
	byrone::InputKey key = byrone::InputManager::inputs[code];

	return !key.previous && key.current;
}

bool byrone::InputManager::isKeyReleased(const sf::Keyboard::Key &code) {
	byrone::InputKey key = byrone::InputManager::inputs[code];

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

	if (event->type != sf::Event::KeyReleased && event->type != sf::Event::KeyPressed) {
		return;
	}

	for (auto k: byrone::InputManager::inputs) {
		if (k.first == event->key.code) {
			byrone::InputManager::inputs[k.first].current = event->type != sf::Event::KeyReleased;
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
