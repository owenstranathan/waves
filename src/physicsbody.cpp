#include "physicsbody.hpp"
#include "utils.hpp"
#include "gravity.hpp"
#include "visitor.hpp"



void PhysicsBody::addForce(const sf::Vector2f& force) { 
	acceleration += force * wabi::Time::deltaTime.count();
}

void PhysicsBody::update(const wabi::duration& deltaTime) {
	if (wabi::squareMagnitude(acceleration) > ALMOST_ZERO) {
		velocity += acceleration * deltaTime.count();
	}
	// position += velocity * deltaTime.count();  // TODO: INCORRECT, REMOVE DELTATIME
	if (wabi::squareMagnitude(velocity) > ALMOST_ZERO) {
		position += velocity * deltaTime.count();  // TODO: INCORRECT, REMOVE DELTATIME
	}
	acceleration *= 0.f;
}

sf::Vector2f PhysicsBody::dragForce(const float fluidDensity = 1)
{
	// sf::Vector2f dragForce = dragCoefficient * sf::Vector2f( -1 * wabi::sign(velocity.x) * (velocity.x * velocity.x), -1 * wabi::sign(velocity.y) *  (velocity.y * velocity.y));
	float dragCoef = 0.5f * fluidDensity * 6.f * rect().area();
	auto velocitySquared = sf::Vector2f(velocity.x * velocity.x, velocity.y * velocity.y);
	auto opposite = sf::Vector2f(-1 * wabi::sign(velocity.x), -1 * wabi::sign(velocity.y));
	return dragCoef * opposite;
}
