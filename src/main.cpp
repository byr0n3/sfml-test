#include <SFML/Graphics.hpp>
#include <iostream>
#include "core/game.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540

std::string getMetricsLabel(sf::Time deltaTime) {
	float ms = deltaTime.asSeconds() * 1000;

	std::string msStr = std::to_string(ms);

	// the warning made me go mad sorry for cast
	for (int i = (int) msStr.length() - 1; i >= 0; i--) {
		if (msStr[i] != '0') {
			break;
		}

		msStr.pop_back();
	}

	// @todo FPS calc might be slightly off
	return "FPS: " + std::to_string((int) (1 / ms * 1000)) +
		   " | Frame time: " + msStr + "ms";
}

int main() {
	sf::VideoMode screenSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// @todo Use 3.3?
	sf::ContextSettings settings(0, 0, 16, 2, 1);

	sf::RenderWindow window = sf::RenderWindow(screenSize, "SFML Test", sf::Style::Default, settings);

	window.setFramerateLimit(144);

	byrone::Game game(SCREEN_WIDTH, SCREEN_HEIGHT);

	game.initialize();

	sf::Clock clock;
	sf::Time current;

	while (game.isOpen()) {
		sf::Time deltaTime = clock.restart();
		current += deltaTime;

		if (current.asMilliseconds() >= 500) {
			window.setTitle(getMetricsLabel(deltaTime));
			current = sf::microseconds(0);
		}

		game.handleEvents(&window);

		if (window.hasFocus()) {
			game.handleInput();
		}

		// @todo Only when focus?
		game.update(deltaTime.asSeconds());
		game.render(&window);
	}

	window.close();
}
