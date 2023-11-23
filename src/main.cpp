#include <SFML/Graphics.hpp>
#include <iostream>
#include "core/game.h"

const int WIDTH = 960;
const int HEIGHT = 540;

int main() {
	auto screenSize = sf::VideoMode(WIDTH, HEIGHT);

	// @todo Use 3.3?
	sf::ContextSettings settings(0, 0, 16, 2, 1);

	sf::RenderWindow window = sf::RenderWindow(screenSize, "SFML Test", sf::Style::Default, settings);

	// window.setFramerateLimit(144);

	byrone::Game game(WIDTH, HEIGHT);

	game.initialize();

	sf::Clock clock;

	while (game.isOpen()) {
		sf::Time deltaTime = clock.restart();

		// std::cout << deltaTime.asMilliseconds() << " ms" << std::endl;

		game.handleInput(&window);

		game.update(deltaTime);

		game.render(&window);
	}

	window.close();
}
