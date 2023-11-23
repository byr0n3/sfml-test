#include "game.h"
#include <SFML/Window/Event.hpp>

const float circleRadius = 50.0f;

byrone::Game::Game(unsigned int width, unsigned int height) : width(width), height(height), open(true) {
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
	this->circle = sf::CircleShape(circleRadius);
	this->circle.setFillColor(sf::Color::Red);

	this->circle.setOutlineThickness(10.0f);
	this->circle.setOutlineColor(sf::Color::Green);

	this->position = sf::Vector2f((this->fWidth() / 2) - circleRadius, (this->fHeight() / 2) - circleRadius);
}

void byrone::Game::handleInput(sf::RenderWindow *window) {
	// handle every event
	for (auto event = sf::Event(); window->pollEvent(event);) {
		switch (event.type) {
			case sf::Event::Closed:
				this->open = false;
				break;

			case sf::Event::KeyPressed:
				if (event.key.scancode == sf::Keyboard::Scancode::Escape) {
					this->open = false;
				}

				break;

			default:
				break;
		}
	}
}

void byrone::Game::update(sf::Time deltaTime) {
	// Run logic here

	sf::Vector2f input(0.0f, 0.0f);

	// coordinates start in top-left corner so we subtract here
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		input.y -= 100.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		input.x -= 100.0f;
	}

	// coordinates start in top-left corner so we add here
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		input.y += 100.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		input.x += 100.0f;
	}

	this->position += input * deltaTime.asSeconds();
}

void byrone::Game::render(sf::RenderWindow *window) {
	// Clear every rendered pixel in the previous frame
	window->clear(sf::Color::Blue);

	// Set the circle's position
	this->circle.setPosition(this->position);

	// Draw our circle
	window->draw(this->circle);

	// Swap buffers to display our new frame
	window->display();
}

void byrone::Game::cleanup() {
	// Dispose/close any streams, unload resources, etc
}
