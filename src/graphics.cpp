#include "graphics.hpp"

sf::RenderTarget& operator<<(sf::RenderTarget& rt, Wave& wave) {		
	static sf::CircleShape point(3);
	point.setFillColor(sf::Color::Black);
	for (int i = 0; i < wave.size; i++) {
		point.setPosition(wabi::brainToScreenSpace(wave.vertices[i]));
		rt.draw(point);
	}
	return rt;
}

sf::RenderTarget& operator<<(sf::RenderTarget& rt, Rock& rock) {
	static sf::CircleShape shape(rock.radius);
	// shape.setFillColor(sf::Color::White);
	shape.setOutlineThickness(4);
	shape.setOutlineColor(sf::Color::Black);
	shape.setPosition(wabi::brainToScreenSpace(rock.position));
	rt.draw(shape);
	return rt;
}