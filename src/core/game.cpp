#include "game.h"
#include <SFML/Window/Event.hpp>

bool limitFrames = true;

byrone::Game::Game(unsigned int width, unsigned int height) : width(width), height(height), open(true),
                                                              player() {
}

byrone::Game::~Game() {
	this->cleanup();
}

unsigned int byrone::Game::getWidth() const {
	return this->width;
}

unsigned int byrone::Game::getHeight() const {
	return this->height;
}

float byrone::Game::fWidth() const {
	return static_cast<float>(this->width);
}

float byrone::Game::fHeight() const {
	return static_cast<float>(this->height);
}

bool byrone::Game::isOpen() const {
	return this->open;
}

void byrone::Game::initialize() {
	auto size = this->player.getSize();

	this->player.setPosition(sf::Vector2f(this->fWidth() / 2 - size.x, this->fHeight() / 2 - size.y));
}

void byrone::Game::handleEvents(sf::RenderWindow *window) {
	// handle every event
	for (auto event = sf::Event(); window->pollEvent(event);) {
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
	}
}

void byrone::Game::handleInput() {
	this->player.handleInput();
}

void byrone::Game::update(float deltaTime) {
	this->player.update(deltaTime);
}

void byrone::Game::render(sf::RenderWindow *window) {
	// Clear every rendered pixel in the previous frame
	window->clear(sf::Color::Blue);

	window->draw(this->player);

	// Swap buffers to display our new frame
	window->display();
}

void byrone::Game::cleanup() {
	// Dispose/close any streams, unload resources, etc
}
