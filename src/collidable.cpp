#include "collidable.hpp"
#include "visitor.hpp"

void* Collidable::accept(Visitor& v) { return v.visit(this); }
