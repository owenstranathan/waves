#include "graphics.hpp"


sf::RenderTarget& operator<<(sf::RenderTarget& rt, Sea& sea) {
	static sf::CircleShape point(3);
	point.setFillColor(sf::Color::Blue);
	for (int i = 0; i < SCREEN_WIDTH; i++) {
		point.setPosition(wabi::brainToScreenSpace(sf::Vector2f(i, sea.level)));
		rt.draw(point);
	}
	for (auto&& wave : sea.waves) {
		rt << *wave;
	}
	return rt;
}

sf::RenderTarget& operator<<(sf::RenderTarget& rt, Wave& wave) {		
	static sf::CircleShape point(3);
	point.setFillColor(sf::Color::Blue);
	for (int i = 0; i < wave.num_vertices; i++) {
		point.setPosition(wabi::brainToScreenSpace(wave.vertices[i]));
		rt.draw(point);
	}
	return rt;
}

sf::RenderTarget& operator<<(sf::RenderTarget& rt, Rock& rock) {
	static sf::CircleShape shape(rock.radius);
	shape.setOutlineThickness(4);
	shape.setOutlineColor(sf::Color::Black);
	shape.setPosition(wabi::brainToScreenSpace(rock.position));
	rt.draw(shape);
	return rt;
}