#include <SFML/Graphics.hpp>
#include "../graphics/texture_sheet.h"
#include "../entities/tile.h"
#include "../core/utilities.h"
#include "editor.h"

int main() {
	sf::VideoMode screenSize(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);

	// @todo Use 3.3?
	sf::ContextSettings settings(0, 0, 16, 2, 1);

	sf::RenderWindow window = sf::RenderWindow(screenSize, "SFML Test - Level Editor", sf::Style::Default, settings);

	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	// @todo Configurable
	byrone::LevelEditor editor("../assets/tilesets/tileset.png", 32);

	bool open = true;
	sf::Clock clock;

	while (open) {
		sf::Time deltaTime = clock.restart();

		open = editor.handleInput(&window);

		if (!window.hasFocus()) {
			continue;
		}

		editor.update(&window, deltaTime.asSeconds());

		editor.draw(&window);

		window.display();
	}

	window.close();

	return 0;
}
