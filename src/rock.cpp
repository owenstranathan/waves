#include "rock.hpp"


void Rock::fixedUpdate() {

}

sf::Rect<float> Rock::rect() {
	return sf::Rect<float>(position.x - radius, position.y + radius, radius, radius);
}