#ifndef BYRONE_GAME
#define BYRONE_GAME

#include <SFML/Graphics/RenderWindow.hpp>
#include "entity.h"
#include "../entities/player.h"
#include "../entities/tile.h"

namespace byrone {
	class Game {
	public:
		Game(unsigned int width, unsigned int height);

		~Game();

		[[nodiscard]] float fWidth() const;

		[[nodiscard]] float fHeight() const;

		[[nodiscard]] bool isOpen() const;

		void initialize();

		void handleEvents(sf::RenderWindow *window);

		void handleInput();

		void update(float deltaTime);

		void render(sf::RenderWindow *window);

		void cleanup();

	private:
		unsigned int width;

		unsigned int height;

		bool open;

		Player player;

		std::vector<Tile> tiles;
	};
}

#endif
