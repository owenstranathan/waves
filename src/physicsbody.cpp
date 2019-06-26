#include "game.hpp"
#include "gravity.hpp"
#include "physicsbody.hpp"
#include "utils.hpp"
#include "visitor.hpp"



void PhysicsBody::addForce(const sf::Vector2f& force) { 
	acceleration += force * game->deltaTime;
}

void PhysicsBody::update(const float deltaTime) {
	velocity += acceleration;
	position += velocity;
	acceleration *= 0.f;
}

sf::Vector2f PhysicsBody::dragForce(const float fluidDensity = 1)
{
	float dragCoef = 0.5f * fluidDensity * 6.f * rect().width;
	auto velocitySquared = sf::Vector2f( -1 * wabi::sign(velocity.x) * velocity.x * velocity.x, -1 * wabi::sign(velocity.y) * velocity.y * velocity.y);
	auto drag = dragCoef * velocitySquared;
	auto squaredTerminalVelocity = 2 * std::abs(Gravity::constant) * game->worldHeight;
	if (wabi::squareMagnitude(drag) > squaredTerminalVelocity) {
		drag = wabi::normalized(drag) * std::sqrt(squaredTerminalVelocity);
	}
	return drag;
}
