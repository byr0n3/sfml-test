#include <SFML/Graphics.hpp>
#include <iostream>

const int WIDTH = 960;
const int HEIGHT = 540;

int main() {
	auto screenSize = sf::VideoMode(WIDTH, HEIGHT);

	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;

	auto window = sf::RenderWindow(screenSize, "SFML Test", sf::Style::Default, settings);

	// window.setFramerateLimit(144);

	bool open = true;

	sf::Clock clock;

	while (open) {
		sf::Time time = clock.restart();
		// @todo Only every half second or so
		std::cout << time.asMilliseconds() << " ms" << std::endl;

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

		window.clear(sf::Color::Blue);

		float radius = 50.0f;

		sf::CircleShape shape(radius);
		shape.setFillColor(sf::Color::Red);

		shape.setOutlineThickness(10.0f);
		shape.setOutlineColor(sf::Color::Green);

		shape.setPosition((static_cast<float>(WIDTH) / 2) - radius, (static_cast<float>(HEIGHT) / 2) - radius);

		window.draw(shape);

		window.display();
	}

	window.close();
}
