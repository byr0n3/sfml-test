#include "../graphics/texture_sheet.h"
#include "../entities/tile.h"
#include "../core/utilities.h"
#include "../core/input_manager.h"
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

			byrone::InputManager::Instance()->handleEvent(&event);
		}

		if (!window.hasFocus()) {
			continue;
		}

		editor.handleInput();

		editor.update(&window, deltaTime.asSeconds());

		editor.draw(&window);

		window.display();

		byrone::InputManager::Instance()->update();
	}

	window.close();

	return 0;
}
