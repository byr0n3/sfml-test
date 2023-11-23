#include "game.h"
#include <SFML/Window/Event.hpp>
#include <iostream>

bool limitFrames = true;

byrone::Game::Game(unsigned int width, unsigned int height) : width(width), height(height), open(true),
															  player(), input(0.0f, 0.0f) {
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
	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("../assets/textures/player.png")) {
		std::cout << "Unable to load player texture." << std::endl;
	}

	sf::Vector2f position(this->fWidth() / 2, this->fHeight() / 2);

	this->player = *new byrone::Entity(playerTexture, position);
	this->player.scale(4.0f, 4.0f);
}

void byrone::Game::handleEvents(sf::RenderWindow *window) {
	// handle every event
	for (auto event = sf::Event(); window->pollEvent(event);) {
		switch (event.type) {
			case sf::Event::Closed:
				this->open = false;
				break;

			case sf::Event::KeyPressed:
				// we don't have to check for focus here

				if (event.key.scancode == sf::Keyboard::Scancode::Escape) {
					this->open = false;
				}

				if (event.key.scancode == sf::Keyboard::Scancode::Tab) {
					limitFrames = !limitFrames;

					window->setFramerateLimit(limitFrames ? 144 : 0);
				}

				break;

			default:
				break;
		}
	}
}

void byrone::Game::handleInput() {
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

void byrone::Game::update(sf::Time deltaTime) {
	this->player.move(this->input * deltaTime.asSeconds());

	this->input = sf::Vector2f(0.0f, 0.0f);
}

void byrone::Game::render(sf::RenderWindow *window) {
	// Clear every rendered pixel in the previous frame
	window->clear(sf::Color::Blue);

	// Draw our player
	window->draw(this->player);

	// Swap buffers to display our new frame
	window->display();
}

void byrone::Game::cleanup() {
	// Dispose/close any streams, unload resources, etc
}