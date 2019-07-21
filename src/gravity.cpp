#include "gravity.hpp"
#include "physicsbody.hpp"

// const float Gravity::constant = -19.8f;
const float Gravity::constant = -9.8f;
const sf::Vector2f Gravity::force = sf::Vector2f(0, Gravity::constant);

void Gravity::apply(PhysicsBody& pb, const float) {
	//pb.velocity += sf::Vector2f(0, constant);
	pb.addForce(force);
}
