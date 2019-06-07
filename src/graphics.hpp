#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "utils.hpp"
#include "prelude.hpp"

#define SEA_COLOR sf::Color::Cyan

class Graphics {
public:

	static void init();
	static void cleanUp();

	static sf::Font * const font;
};


sf::RenderTarget& operator<<(sf::RenderTarget& rt, const Game& game);
sf::RenderTarget& operator<<(sf::RenderTarget &rt, const Sea& sea);
sf::RenderTarget& operator<<(sf::RenderTarget &rt,  const Wave& wave);
sf::RenderTarget& operator<<(sf::RenderTarget &rt, const Rock& rock);

#endif // !GRAPHICS_HPP
