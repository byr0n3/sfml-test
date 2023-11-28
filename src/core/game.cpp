#include "game.h"
#include "../exceptions/texture_load_exception.h"
#include <SFML/Window/Event.hpp>
#include <cmath>

bool limitFrames = true;

// @todo Tiles class?
void generateFloor(byrone::Game *game) {
	sf::Texture tilesetTexture;
	if (!tilesetTexture.loadFromFile("../assets/tileset.png")) {
		throw byrone::texture_load_exception("../assets/tileset.png");
	}

	sf::Vector2i tileSize(32, 32);
	game->tilesSheet = byrone::TextureSheet(tilesetTexture, tileSize);

	// tiles needed to fill a row (- 2 to keep a gap on the left and right)
	int count = std::ceil(game->fWidth() / (float) (tileSize.x)) - 2;
	float y = game->fHeight() - (float) (tileSize.y);

	game->tiles = std::vector<byrone::Tile>(count);

	for (int i = 0; i < count; i++) {
		int spriteIdx = (i == 0 ? TILE_TOP_LEFT_IDX : (i == count - 1 ? TILE_TOP_RIGHT_IDX : TILE_CENTER_IDX));

		// add a tile sized gap to center the tiles
		sf::Vector2f position((tileSize.x * i) + tileSize.x, y);
		byrone::Tile tile(&game->tilesSheet, spriteIdx, position);

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
	sf::Vector2i size = this->player.getSize();

	// skip a tile on X and Y axis
	this->player.setPosition(sf::Vector2f(size.x * 2.0f, this->fHeight() - (size.y * 2.0f)));

	generateFloor(this);
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
	}
}

void byrone::Game::handleInput() {
	this->player.handleInput();
}

void byrone::Game::update(float deltaTime) {
	this->player.update(deltaTime, &this->tiles);
}

void byrone::Game::render(sf::RenderWindow *window) {
	// Clear every rendered pixel in the previous frame
	window->clear(sf::Color::Blue);

	for (const byrone::Tile &tile: this->tiles) {
		window->draw(tile);
	}

	window->draw(this->player);

	// Swap buffers to display our new frame
	window->display();
}

void byrone::Game::cleanup() {
	// Dispose/close any streams, unload resources, etc
}
