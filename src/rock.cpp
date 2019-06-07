#include "rock.hpp"
#include "visitor.hpp"

void Rock::accept(Visitor& v) { v.visit(this); }

sf::FloatRect Rock::rect() const {
	return sf::Rect<float>(position.x - radius, position.y + radius, radius, radius);
}


