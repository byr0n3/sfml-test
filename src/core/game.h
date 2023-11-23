#ifndef BYRONE_GAME
#define BYRONE_GAME

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>

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

		void handleInput(sf::RenderWindow *window);

		void update(sf::Time deltaTime);

		void render(sf::RenderWindow *window);

		void cleanup();

	private:
		unsigned int width;

		unsigned int height;

		bool open;

		// Testing variables

		sf::CircleShape circle;

		sf::Vector2f position;
	};
}

#endif
