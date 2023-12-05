#ifndef BYRONE_STORABLE_TILE
#define BYRONE_STORABLE_TILE

#include <SFML/System/Vector2.hpp>

namespace byrone {
	class StorableTile {
	public:
		StorableTile();

		StorableTile(const int &textureIdx, const sf::Vector2f &position);

		void setTextureIdx(const int &newTextureIdx);

		[[nodiscard]] int getTextureIdx() const;

		[[nodiscard]] sf::Vector2f getPosition() const;

	private:
		int textureIdx;
		sf::Vector2f position;
	};
}

#endif
