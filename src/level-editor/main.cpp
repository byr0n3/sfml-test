#include <SFML/Graphics.hpp>
#include "../graphics/texturesheet.h"
#include "../entities/tile.h"
#include "../core/utilities.h"
#include "editor.h"

int main() {
	sf::VideoMode screenSize(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);

	// @todo Use 3.3?
	sf::ContextSettings settings(0, 0, 16, 2, 1);

	auto style = sf::Style::Titlebar | sf::Style::Close;
	sf::RenderWindow window = sf::RenderWindow(screenSize, "SFML Test - Level Editor", style, settings);

	window.setFramerateLimit(60);

	// @todo Configurable
	byrone::LevelEditor editor("../assets/tilesets/tileset.png", 32);

	bool open = true;

	while (open) {
		for (sf::Event event = sf::Event(); window.pollEvent(event);) {
			switch (event.type) {
				case sf::Event::Closed:
					open = false;
					break;

				case sf::Event::KeyPressed: {
					if (event.key.scancode == sf::Keyboard::Scancode::Escape) {
						open = false;
					}

					break;
				}

				default:
					break;
			}
		}

		if (!window.hasFocus()) {
			continue;
		}

		editor.update(window);

		editor.draw(&window);

		window.display();
	}

	window.close();

	return 0;
}
