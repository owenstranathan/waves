#include "gravity.hpp"
#include "physicsbody.hpp"

// const float Gravity::constant = -19.8f;
const float Gravity::constant = -9.8f;

void Gravity::apply(PhysicsBody& pb, wabi::duration deltaTime) {
	pb.velocity += sf::Vector2f(0, constant);
	// pb.addForce(sf::Vector2f(0, pb.mass() * constant));
}
