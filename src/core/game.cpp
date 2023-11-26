#include "game.h"
#include "../exceptions/texture_load_exception.h"
#include <SFML/Window/Event.hpp>
#include <cmath>

bool limitFrames = true;
byrone::TextureSheet tileset;

// @todo Tiles class?
void generateFloor(byrone::Game *game) {
	sf::Texture tilesetTexture;
	if (!tilesetTexture.loadFromFile("../assets/tileset.png")) {
		throw byrone::texture_load_exception("../assets/tileset.png");
	}

	sf::Vector2i tileSize(32, 32);
	tileset = byrone::TextureSheet(tilesetTexture, tileSize);

	int count = std::ceil(game->fWidth() / (float) (tileSize.x * 2));
	float y = game->fHeight() - (float) (tileSize.y * 2);

	game->tiles = std::vector<byrone::Tile>(count);

	for (int i = 0; i < count; i++) {
		sf::Vector2f position((tileSize.x * 2) * i, y);
		byrone::Tile tile(&tileset, position);

		game->tiles[i] = tile;
	}
}

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
	auto size = this->player.getSize();

	this->player.setPosition(sf::Vector2f(this->fWidth() / 2 - size.x, this->fHeight() / 2 - size.y));

	generateFloor(this);
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

	for (const auto &tile: this->tiles) {
		window->draw(tile);
	}

	// Swap buffers to display our new frame
	window->display();
}

void byrone::Game::cleanup() {
	// Dispose/close any streams, unload resources, etc
}
