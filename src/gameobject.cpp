#include "gameobject.hpp"
#include "visitor.hpp"

int GameObject::_seed_id = 0;

GameObject::GameObject(): id(++_seed_id), game(nullptr) { }

