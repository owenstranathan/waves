#include "gameobject.hpp"
#include "visitor.hpp"

int GameObject::_seed_id = 0;

GameObject::GameObject(): game(nullptr), id(++_seed_id) { }

