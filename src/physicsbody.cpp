#include <iostream>

#include "game.hpp"
#include "gravity.hpp"
#include "physicsbody.hpp"
#include "utils.hpp"
#include "visitor.hpp"

void PhysicsBody::addForce(const sf::Vector2f &force)
{
    if (isKinematic)
        return;
    // acceleration += force * game->deltaTime;
	if (force.x != 0)
		std::cout << "fuck";
    velocity += force * game->deltaTime;
}

float PhysicsBody::impulse(const PhysicsBody& pb) const {
	float reducedMass = (mass() * pb.mass()) / (mass() + pb.mass());
	float coefficent = 1 + coefficientOfRestitution;
	float velocityDiff = wabi::magnitude(velocity) - wabi::magnitude(coefficientOfRestitution * velocity);
	return reducedMass * coefficent * velocityDiff;
}

void PhysicsBody::update(const float deltaTime)
{
    if (isKinematic)
        return;
    velocity += acceleration;
    position += velocity;
    acceleration *= 0.f;
}

sf::Vector2f PhysicsBody::dragForce(const float fluidDensity = 1)
{
    float dragCoef = 0.5f * fluidDensity * 6.f * rect().width;
    auto velocitySquared = sf::Vector2f(-1 * wabi::sign(velocity.x) * velocity.x * velocity.x, -1 * wabi::sign(velocity.y) * velocity.y * velocity.y);
    auto drag = dragCoef * velocitySquared;
    auto squaredTerminalVelocity = 2 * std::abs(Gravity::constant) * game->worldHeight;
    if (wabi::squareMagnitude(drag) > squaredTerminalVelocity)
    {
        drag = wabi::normalized(drag) * std::sqrt(squaredTerminalVelocity);
    }
    return drag;
}
