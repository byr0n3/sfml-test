#ifndef BYRONE_GAME
#define BYRONE_GAME

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "entity.h"

namespace byrone {
	class Game {
	public:
		Game(unsigned int width, unsigned int height);

		~Game();

		[[nodiscard]] unsigned int getWidth() const;

		[[nodiscard]] unsigned int getHeight() const;

		[[nodiscard]] float fWidth() const;

		[[nodiscard]] float fHeight() const;

		[[nodiscard]] bool isOpen() const;

		void initialize();

		void handleEvents(sf::RenderWindow *window);

		void handleInput();

		void update(sf::Time deltaTime);

		void render(sf::RenderWindow *window);

		void cleanup();

	private:
		unsigned int width;

		unsigned int height;

		bool open;

		Entity player;

		// @todo Move?
		sf::Vector2f input;
	};
}

#endif