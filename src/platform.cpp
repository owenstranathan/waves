#include <iostream>

#include "platform.hpp"
#include "ship.hpp"
#include "rock.hpp"

Platform::Platform(sf::Vector2f pos, float w, float h) : width(w), height(h)
{
	position = pos;
	isKinematic = true;
}

Platform::~Platform() {}

wabi::Rectf Platform::rect() const { return wabi::Rectf(sf::Vector2f(position.x - width/2, position.y+height/2), sf::Vector2f(width, height)); }

void Platform::accept(Visitor &v) { v.visit(this); };

void Platform::accept(CollisionVisitor &v, Collidable *c) { v.visit(this, c); };

void Platform::collisionEnter(Ship *ship)
{
	auto platformRect = rect();
	auto shipRect = ship->rect();
	wabi::Rectf overlap;
	platformRect.intersects(shipRect, overlap);
	auto relPos = ship->position - platformRect.center(); // TODO: fix platform position so you don't need rect.center
	auto normalizedRelPos = wabi::normalized(relPos);
	auto correction = -1.0f * wabi::normalized(ship->velocity);
	correction.x *= overlap.width + 0.1;
	correction.y *= overlap.height + 0.1;
	ship->position += correction;
	ship->velocity *= 0.f;
	relPos = ship->position - platformRect.center(); // TODO: fix platform position so you don't need rect.center
	normalizedRelPos = wabi::normalized(relPos);
	sf::Vector2f collisionNormal = normalizedRelPos; // default (colliding corner to corner)
	if (ship->position.x < platformRect.left || ship->position.x > platformRect.right()) {
		// On left or right of platform normal becomes (+/- 1, 0)
		collisionNormal.y = 0.f;
	}
	else if (ship->position.y < platformRect.bottom() || ship->position.y > platformRect.top) {
		// On top or bottom of platform normal becomes (0, +/- 1)
		collisionNormal.x = 0.f;
	}
	auto J = ship->impulse(*this);
	auto correctiveForce = (J / ship->mass()) * collisionNormal;
	ship->addForce(correctiveForce);
}

void Platform::collisionStay(Ship *ship) { collisionEnter(ship); }

void Platform::collisionExit(Ship *) {}

void Platform::collisionEnter(Rock *) { }

void Platform::collisionStay(Rock *rock) { collisionEnter(rock); }
void Platform::collisionExit(Rock *) {}
