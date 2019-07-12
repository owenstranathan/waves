#include <iostream>
#include <cassert>

#include "collisionsystem.hpp"
#include "collidable.hpp"
#include "game.hpp"
#include "sea.hpp"
#include "ship.hpp"
#include "wave.hpp"
#include "rock.hpp"

const auto by_x = [](Collidable *a, Collidable *b) -> bool { return a->rect().left < b->rect().left; };
const auto by_y = [](Collidable *a, Collidable *b) -> bool { return a->rect().top < b->rect().top; };

CollisionSystem::CollisionSystem(Game *g) : game(g) {}

void CollisionSystem::addCollidable(Collidable *collidable)
{
    wabi::insert_sorted(sortedByX, collidable, by_x);
    wabi::insert_sorted(sortedByY, collidable, by_y);
}

void CollisionSystem::removeCollidable(Collidable *collidable)
{
    // TODO: Fix bug where colliders are getting left in the map.
    // NOTE: I think it has something todo with the timing of removal
    // The problem can be reproduced by having 2 rocks overlap on some axis
    sortedByX.remove(collidable);
    sortedByY.remove(collidable);
    for (auto key : key2Id[collidable->id])
    {
        // remove the key from the colliders (because the pair is not invalid)
        activePairs.remove(colliders[key].pair);
        previouslyActivePairs.remove(colliders[key].pair);
        colliders.erase(key);
        // colliders.remove(key);
        // get the id for the other collider in this key pair;
        unsigned int otherId = (key.first == collidable->id) ? key.second : key.first;
        key2Id[otherId].remove(key);
    }
    key2Id.erase(collidable->id);
    // activePairs.clear();
}

void CollisionSystem::sweepAxis(
    unsigned int axis,
    std::list<Collidable *> &collidables,
    std::function<bool(wabi::Rectf, wabi::Rectf)> compare,
    std::function<float(wabi::Rectf)> little,
    std::function<float(wabi::Rectf)> big)
{
    // Uses broad phase sweep and prune to determine a rough list of active Collidable pairs
    if (collidables.size() < 2)
    {
        return;
    }
    float max = big((*collidables.begin())->rect());
    for (auto c = std::next(collidables.begin()); c != collidables.end(); c = std::next(c))
    {
        auto collidable = *c;
        auto colliderRect = collidable->rect();
        auto a = c;
        do
        {
            a = std::prev(a);
            auto active = *a;
            auto activeRect = active->rect();
            auto key = make_ordered_pair(collidable->id, active->id, [](int x) -> int { return x; });
            if (compare(colliderRect, activeRect))
            {
                activateColliderForAxis(collidable, active, axis);
            }
            else
            {
                colliders[key].mask &= ~axis;
            }
            if (little(colliderRect) > max)
            {
                break;
            }
        } while (a != collidables.begin());
        if (big(colliderRect) > max)
        {
            max = big(colliderRect);
        }
    }
}

void CollisionSystem::resolveCollisions()
{
    wabi::insertion_sort<Collidable *>(sortedByX.begin(), sortedByX.end(), by_x);
    wabi::insertion_sort<Collidable *>(sortedByY.begin(), sortedByY.end(), by_y);
    previouslyActivePairs.clear();
    previouslyActivePairs.swap(activePairs);
    sweepAxis(
        X_AXIS,
        sortedByX,
        [](wabi::Rectf r1, wabi::Rectf r2) -> bool { return r1.left < r2.right(); },
        [](wabi::Rectf r) -> float { return r.left; },
        [](wabi::Rectf r) -> float { return r.right(); });
    sweepAxis(
        Y_AXIS,
        sortedByY,
        [](wabi::Rectf r1, wabi::Rectf r2) -> bool { return r1.bottom() < r2.top; },
        [](wabi::Rectf r) -> float { return r.bottom(); },
        [](wabi::Rectf r) -> float { return r.top; });
    // for every pair we have determined is maybe colliding. Because type resolution is so hard we leave it to
    // the class to determine if and how another object is truely colliding with it.
    EnterVisitor enter; // dispatch collisionEnter
    StayVisitor stay;   // dispatch collisionStay
    ExitVisitor exit;   // dispatch collisionExit
    for (auto &&pair : activePairs)
    {
        // if the collider was previously active
        auto search = std::find(previouslyActivePairs.begin(), previouslyActivePairs.end(), pair);
        if (search != previouslyActivePairs.end())
        {
            pair.first->accept(stay, pair.second);
            // Remove this pair from the list of previously colliding pairs so that when we're
            // done all that is left is pairs that were colliding previously but are not anymore.
            previouslyActivePairs.remove(pair);
        }
        else
        {
            // otherwise the collider is newly colliding
            pair.first->accept(enter, pair.second);
        }
    }
    // every pair left in the previouslyActive list is no longer colliding and should exit their collision;
    for (auto &&pair : previouslyActivePairs)
    {
        pair.first->accept(exit, pair.second);
    }
}

void CollisionSystem::clear()
{
    sortedByX.clear();
    sortedByY.clear();
    colliders.clear();
    key2Id.clear();
}

size_t CollisionSystem::size() const
{
    assert(sortedByX.size() == sortedByY.size());
    return sortedByX.size();
}

// Adds a collider object to the colliders unordered_map and sets it's mask for the given
// Axis. Also does some book keeping to try and keep track of which pairs exist for which colliders
void CollisionSystem::activateColliderForAxis(Collidable *c1, Collidable *c2, unsigned int axis)
{
    auto key = make_ordered_pair(c1->id, c2->id, [](int x) -> int { return x; });
    colliders[key].pair = make_ordered_pair(c1, c2, [](Collidable *c) -> int { return c->id; });
    colliders[key].mask |= axis;
    // seenKeys.insert(key);
    if (colliders[key].colliding())
    {
        // don't add the same pair twice;
        auto search = std::find(activePairs.begin(), activePairs.end(), colliders[key].pair);
        if (search == activePairs.end())
        {
            activePairs.push_back(colliders[key].pair);
        }
    }
    std::list<std::pair<int, int>> c1IdList = key2Id[c1->id];
    std::list<std::pair<int, int>> c2IdList = key2Id[c2->id];
    if (auto search = std::find(c1IdList.begin(), c1IdList.end(), key) == c1IdList.end())
    {
        key2Id[c1->id].push_back(key);
    }
    if (auto search = std::find(c2IdList.begin(), c2IdList.end(), key) == c2IdList.end())
    {
        key2Id[c2->id].push_back(key);
    }
}

// CollisionEnter
void EnterVisitor::visit(Collidable *c1, Collidable *c2)
{
    c1->collisionEnter(c2);
}

void EnterVisitor::visit(PhysicsBody *pb, Collidable *c)
{
    c->collisionEnter(pb);
}

void EnterVisitor::visit(Sea *sea, Collidable *c)
{
    c->collisionEnter(sea);
}

void EnterVisitor::visit(Rock *rock, Collidable *c)
{
    c->collisionEnter(rock);
}

void EnterVisitor::visit(Wave *wave, Collidable *c)
{
    c->collisionEnter(wave);
}

void EnterVisitor::visit(Ship *ship, Collidable *c)
{
    c->collisionEnter(ship);
}

//Collision Stay
void StayVisitor::visit(Collidable *c1, Collidable *c2)
{
    c1->collisionStay(c2);
}

void StayVisitor::visit(PhysicsBody *pb, Collidable *c)
{
    c->collisionStay(pb);
}

void StayVisitor::visit(Sea *sea, Collidable *c)
{
    c->collisionStay(sea);
}

void StayVisitor::visit(Rock *rock, Collidable *c)
{
    c->collisionStay(rock);
}

void StayVisitor::visit(Wave *wave, Collidable *c)
{
    c->collisionStay(wave);
}

void StayVisitor::visit(Ship *ship, Collidable *c)
{
    c->collisionStay(ship);
}

//Collision Stay
void ExitVisitor::visit(Collidable *c1, Collidable *c2)
{
    c1->collisionExit(c2);
}

void ExitVisitor::visit(PhysicsBody *pb, Collidable *c)
{
    c->collisionExit(pb);
}

void ExitVisitor::visit(Sea *sea, Collidable *c)
{
    c->collisionExit(sea);
}

void ExitVisitor::visit(Rock *rock, Collidable *c)
{
    c->collisionExit(rock);
}

void ExitVisitor::visit(Wave *wave, Collidable *c)
{
    c->collisionExit(wave);
}

void ExitVisitor::visit(Ship *ship, Collidable *c)
{
    c->collisionExit(ship);
}
