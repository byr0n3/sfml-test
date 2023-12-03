#ifndef BYRONE_INPUT_MANAGER
#define BYRONE_INPUT_MANAGER

#include <cstdio>
#include <SFML/Graphics.hpp>

namespace byrone {
	struct InputKey {
		bool current;
		bool previous;

		InputKey();
	};

	class InputManager {
	public:
		static InputManager *Instance();

		bool isKeyDown(const sf::Keyboard::Key &code);

		bool isKeyUp(const sf::Keyboard::Key &code);

		bool isKeyPressed(const sf::Keyboard::Key &code);

		bool isKeyReleased(const sf::Keyboard::Key &code);

		[[nodiscard]] float getMouseDelta() const;

		void update();

		void handleEvent(const sf::Event *event);

	private:
		static InputManager *instance;

		InputManager();

		std::unordered_map<sf::Keyboard::Key, byrone::InputKey> inputs;
		float mouseDelta;
	};
}

#endif
