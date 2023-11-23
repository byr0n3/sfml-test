#ifndef BYRONE_ENTITY
#define BYRONE_ENTITY

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace byrone {
	// @todo Add destructor?
	class Entity : public sf::Drawable, public sf::Transformable {
	public:
		Entity();

		Entity(const sf::Texture &texture,
			   sf::Vector2f position = sf::Vector2f(0.0f, 0.0f),
			   float rotation = 0.0f,
			   sf::Vector2f scale = sf::Vector2f(1.0f, 1.0f),
			   sf::Color color = sf::Color::White);

	private:
		sf::Color color;

		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		sf::VertexArray m_vertices;
		sf::Texture m_texture;
	};
}


#endif
