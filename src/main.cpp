#include <SFML/Graphics.hpp>

int main() {
	auto screenSize = sf::VideoMode(960, 540);
	auto window = sf::RenderWindow(screenSize, "SFML Test");

	// window.setFramerateLimit(144);

	bool open = true;

	while (open) {
		// handle every event
		for (auto event = sf::Event(); window.pollEvent(event);) {
			switch (event.type) {
				case sf::Event::Closed:
					open = false;
					break;

				case sf::Event::KeyPressed:
					if (event.key.scancode == sf::Keyboard::Scancode::Escape) {
						open = false;
					}

					break;

				default:
					break;
			}
		}

		window.clear();
		window.display();
	}

	window.close();
}
