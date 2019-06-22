#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "utils.hpp"
#include "prelude.hpp"

#define SEA_COLOR sf::Color::Cyan

class Graphics {
public:

	static void init();
	static void cleanUp();

	static sf::Font* const font;
	static sf::Text* const text;
};


sf::RenderTarget& operator<<(sf::RenderTarget&, const Game&);
sf::RenderTarget& operator<<(sf::RenderTarget&, const CollisionSystem&);
sf::RenderTarget& operator<<(sf::RenderTarget&, const Sea&);
sf::RenderTarget& operator<<(sf::RenderTarget&, const Wave&);
sf::RenderTarget& operator<<(sf::RenderTarget&, const Rock&);
sf::RenderTarget& operator<<(sf::RenderTarget&, const Ship&);

template <typename T>
void drawRect(sf::RenderTarget& rt, const wabi::Rect<T>& rect, sf::Color color);

#endif // !GRAPHICS_HPP
