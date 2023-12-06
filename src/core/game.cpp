#include "game.h"
#include "../exceptions/load_file_exception.h"
#include "input_manager.h"
#include <SFML/Window/Event.hpp>

bool limitFrames = true;

byrone::Game::Game(unsigned int width, unsigned int height) : width(width), height(height), open(true),
															  player() {
}

byrone::Game::~Game() {
	this->cleanup();
}

float byrone::Game::fWidth() const {
	return (float) this->width;
}

float byrone::Game::fHeight() const {
	return (float) this->height;
}

bool byrone::Game::isOpen() const {
	return this->open;
}

void byrone::Game::initialize() {
	this->level = byrone::Level::readFromFile("../assets/levels/custom.lvl");

	this->player.setPosition(this->level.getPlayerPosition());
}

void byrone::Game::handleEvents(sf::RenderWindow *window) {
	// handle every event
	for (sf::Event event = sf::Event(); window->pollEvent(event);) {
		switch (event.type) {
			case sf::Event::Closed: {
				this->open = false;
				return;
			}

			case sf::Event::KeyPressed: {
				// we don't have to check for focus here

				if (event.key.scancode == sf::Keyboard::Scancode::Escape) {
					this->open = false;
					return;
				}

				if (event.key.scancode == sf::Keyboard::Scancode::Tab) {
					limitFrames = !limitFrames;

					window->setFramerateLimit(limitFrames ? 144 : 0);
				}

				break;
			}

			default:
				break;
		}

		byrone::InputManager::Instance()->handleEvent(&event);
	}
}

void byrone::Game::handleInput(const float &deltaTime) {
	this->player.handleInput(deltaTime);
}

void byrone::Game::update(const float &deltaTime) {
	this->player.update(deltaTime, &this->level);

	byrone::InputManager::Instance()->update();
}

void byrone::Game::render(sf::RenderWindow *window) {
	// Clear every rendered pixel in the previous frame
	window->clear(sf::Color::Blue);

	this->level.draw(window);

	window->draw(this->player);

	// Swap buffers to display our new frame
	window->display();
}

void byrone::Game::cleanup() {
	// Dispose/close any streams, unload resources, etc
}
