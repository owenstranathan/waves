#include "graphics.hpp"


sf::RenderTarget& operator<<(sf::RenderTarget& rt, Sea& sea) {
	std::vector<sf::Vertex> vertices;
	for (int i = 0; i < SCREEN_WIDTH; i += 1) {
		vertices.push_back(sf::Vertex(wabi::brainToScreenSpace(sf::Vector2f(i, (int)sea.height(i))), SEA_COLOR));
		// vertices.push_back(sf::Vertex(sf::Vector2f(i, SCREEN_HEIGHT), SEA_COLOR));
	}
	// rt.draw(&vertices[0], vertices.size(), sf::TriangleStrip);
	rt.draw(&vertices[0], vertices.size(), sf::LineStrip);
	return rt;
}

sf::RenderTarget& operator<<(sf::RenderTarget& rt, Wave& wave) {		
	// static sf::CircleShape point(3);
	// point.setFillColor(sf::Color::Blue);
	// for (int i = 0; i < wave.num_vertices; i++) {
	// 	point.setPosition(wabi::brainToScreenSpace(wave.vertices[i]));
	// 	rt.draw(point);
	// }
	return rt;
}

sf::RenderTarget& operator<<(sf::RenderTarget& rt, Rock& rock) {
	static sf::CircleShape shape(rock.radius);
	shape.setOutlineThickness(4);
	shape.setOutlineColor(sf::Color(204, 51, 0));
	shape.setFillColor(sf::Color(0, 0, 0, 0));
	shape.setOrigin(sf::Vector2f(rock.radius, rock.radius));
	shape.setPosition(wabi::brainToScreenSpace(rock.position));
	rt.draw(shape);
	return rt;
}