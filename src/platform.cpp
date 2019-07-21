#include <iostream>

#include "platform.hpp"
#include "ship.hpp"

Platform::Platform(sf::Vector2f pos, float w, float h) : width(w), height(h)
{
	position = pos;
	isKinematic = true;
}

Platform::~Platform() {}

wabi::Rectf Platform::rect() const { return wabi::Rectf(position, sf::Vector2f(width, height)); }

void Platform::accept(Visitor &v) { v.visit(this); };

void Platform::accept(CollisionVisitor &v, Collidable *c) { v.visit(this, c); };

void Platform::collisionEnter(Ship *ship)
{
	// This is not the most amazing way for this to work, but it works
	// and good enough is good enough. Next time use a proper physics engine
	auto myRect = rect();
	auto shipRect = ship->rect();
	auto relPos = myRect.center() - ship->position;
	if (wabi::dot(ship->velocity, wabi::normalized(relPos)) <= 0.f){
		// if velocity will separate us then do nothing
		return;
	}
	wabi::Rectf overlap;
	myRect.intersects(shipRect, overlap);
	if (shipRect.bottom() - myRect.top > -0.5f && shipRect.top > myRect.top)
	{
		// then we're falling onto the platform
		ship->velocity.y = 0.f;
		ship->position.y += overlap.height;
		ship->addForce(ship->dragForce(1));
	}
	else
	{
		auto restitutionForce = mass() * ship->velocity * -overlap.area();
		// magic ! (you're a wizard harry)
		float maxMag = 200.f;
		if (wabi::squareMagnitude(restitutionForce) > maxMag * maxMag){
			restitutionForce = wabi::normalized(restitutionForce) * maxMag;
		}
		ship->addForce(restitutionForce);
		// ship->addForce(ship->dragForce(1));
	}
}

void Platform::collisionStay(Ship *ship) { collisionEnter(ship); }

void Platform::collisionExit(Ship *) {}
