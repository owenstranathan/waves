#include "collidable.hpp"
#include "visitor.hpp"

void Collidable::accept(Visitor &v) { return v.visit(this); }

void Collidable::accept(CollisionVisitor &v, Collidable *c) { return v.visit(this, c); }

// collisionEnter
void Collidable::collisionEnter(Collidable *) {}
void Collidable::collisionEnter(Sea *) {}
void Collidable::collisionEnter(Ship *) {}
void Collidable::collisionEnter(Rock *) {}
void Collidable::collisionEnter(Wave *) {}
void Collidable::collisionEnter(Platform *) {}

// collisionStay
void Collidable::collisionStay(Collidable *) {}
void Collidable::collisionStay(Sea *) {}
void Collidable::collisionStay(Ship *) {}
void Collidable::collisionStay(Rock *) {}
void Collidable::collisionStay(Wave *) {}
void Collidable::collisionStay(Platform *) {}

// collisionExit
void Collidable::collisionExit(Collidable *) {}
void Collidable::collisionExit(Sea *) {}
void Collidable::collisionExit(Ship *) {}
void Collidable::collisionExit(Rock *) {}
void Collidable::collisionExit(Wave *) {}
void Collidable::collisionExit(Platform *) {}
