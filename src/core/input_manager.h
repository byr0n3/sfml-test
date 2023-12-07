#ifndef BYRONE_INPUT_MANAGER
#define BYRONE_INPUT_MANAGER

#include <cstdio>
#include <SFML/Graphics.hpp>
#include <unordered_map>

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

		bool isMouseDown(const sf::Mouse::Button &button);

		bool isMouseUp(const sf::Mouse::Button &button);

		bool isMousePressed(const sf::Mouse::Button &button);

		bool isMouseReleased(const sf::Mouse::Button &button);

		[[nodiscard]] float getMouseDelta() const;

		void update();

		void handleEvent(const sf::Event *event);

	private:
		static InputManager *instance;

		InputManager();

		std::unordered_map<int, byrone::InputKey> inputs;
		float mouseDelta;
	};
}

#endif
