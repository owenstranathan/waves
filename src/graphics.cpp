#include <iostream>
#include <sstream>

#include "graphics.hpp"
#include "game.hpp"
#include "sea.hpp"
#include "ship.hpp"
#include "wave.hpp"
#include "rock.hpp"
#include "rect.hpp"

// We set these in the Graphics object constructor, attempting to use the
// statics without first initializing an instance of a graphics object
// is undefined. (it's just zero, but your whole game is gonna be fucky)
float Graphics::pixelsPerUnit = 0;
int Graphics::SCREEN_WIDTH = 0;
int Graphics::SCREEN_HEIGHT = 0;

Graphics::Graphics(Game *g, sf::RenderTarget *rt, sf::VideoMode &vm) : font(new sf::Font()), text(new sf::Text()), game(g), target(rt)
{
    SCREEN_HEIGHT = vm.height;
    SCREEN_WIDTH = vm.width;
    pixelsPerUnit = SCREEN_WIDTH / game->worldWidth;
    font->loadFromFile("assets/fonts/IBMPlexMono-Regular.ttf");
    text->setFont(*Graphics::font);
    text->setFillColor(sf::Color::White);
    text->setCharacterSize(15);
}

Graphics::~Graphics()
{
    delete font;
    delete text;
}

void Graphics::draw() const
{
    target->clear(sf::Color::Black);
    draw(*game->sea);
    for (auto &&rock : game->rocks)
    {
        draw(*rock);
    }
    draw(*game->ship);

    std::stringstream infostream;
    infostream << "FrameRate    : " << 1 / game->deltaTime << std::endl;
    infostream << "deltaTime    : " << game->deltaTime << std::endl;
    infostream << "# waves		: " << game->waves.size() << std::endl;
    infostream << "# rocks		: " << game->rocks.size() << std::endl;
    infostream << "# colliders	: " << game->collisionSystem.size() << std::endl;
    infostream << "ship pos		: " << game->ship->position << std::endl;
    infostream << "ship vel		: " << game->ship->velocity << std::endl;
    infostream << "ship accl	: " << game->ship->acceleration << std::endl;

    text->setString(infostream.str());
    text->setPosition(3, 3);
    target->draw(*text);

    std::stringstream colliderPairStream;
    for (auto &&p : game->collisionSystem.colliders)
    {
        auto key = p.first;
        colliderPairStream << "(" << key.first << ", " << key.second << ") \n";
    }
    infostream << "pairs: \n"
               << colliderPairStream.str() << std::endl;
    text->setString(colliderPairStream.str());
    auto textRect = text->getGlobalBounds();
    text->setPosition(SCREEN_WIDTH - textRect.width, 3);
    target->draw(*text);

#if _DEBUG
    draw(game->collisionSystem);
#endif
}

void Graphics::draw(const CollisionSystem &collisionSystem) const
{
    for (auto &&collider : collisionSystem.collidables())
    {
        draw(*collider, sf::Color::Green);
    }
    for (auto &&pair : collisionSystem.activePairs)
    {
        draw(*pair.first, sf::Color::Red);
        draw(*pair.second, sf::Color::Red);
    }
}

void Graphics::draw(const Sea &sea) const
{
    static std::vector<sf::Vertex> vertices;
    float step = 1 / pixelsPerUnit;
    for (float i = 0; i < game->worldWidth; i += step)
    {
        vertices.push_back(sf::Vertex(game2ScreenPos(sf::Vector2f(i, sea.height(i))), SEA_COLOR));
        vertices.push_back(sf::Vertex(game2ScreenPos(sf::Vector2f(i, 0)), SEA_COLOR));
    }
    target->draw(&vertices[0], vertices.size(), sf::TriangleStrip);
    vertices.clear();
}

void Graphics::draw(const Rock &rock) const
{
    static sf::CircleShape shape(rock.radius * pixelsPerUnit);
    shape.setOutlineThickness(4);
    shape.setOutlineColor(sf::Color(204, 51, 0));
    shape.setFillColor(sf::Color(0, 0, 0, 0));
    shape.setOrigin(sf::Vector2f(rock.radius * pixelsPerUnit, rock.radius * pixelsPerUnit));
    shape.setPosition(game2ScreenPos(rock.position));
    target->draw(shape);
}

void Graphics::draw(const Ship &ship) const
{
    draw(game2ScreenRect(ship.rect()), sf::Color::Magenta);
}

void Graphics::draw(const Collidable &collider, sf::Color color) const
{
    auto screenRect = game2ScreenRect(collider.rect());
    draw(screenRect, color);
    text->setString(std::to_string(collider.id));
    text->setFillColor(sf::Color::White);
    auto textRect = text->getGlobalBounds();
    text->setOrigin(textRect.width / 2, textRect.height / 2);
    text->setPosition(sf::Vector2f(screenRect.left + screenRect.width / 2, screenRect.top + screenRect.height / 2));
    target->draw(*text);
    text->setOrigin(0, 0);
}

template <typename T>
void Graphics::draw(const wabi::Rect<T> &rect, sf::Color color) const
{
    auto screenRect = game2ScreenRect(rect);
    static sf::RectangleShape rectShape;
    rectShape.setOutlineColor(color);
    rectShape.setOutlineThickness(3);
    rectShape.setFillColor(sf::Color(0, 0, 0, 0));
    rectShape.setSize(sf::Vector2f(screenRect.width, screenRect.height));
    rectShape.setPosition(sf::Vector2f(rect.left, rect.top));
    target->draw(rectShape);
}

template <typename T>
void Graphics::draw(const sf::Rect<T> &rect, sf::Color color) const
{
    static sf::RectangleShape rectShape;
    rectShape.setOutlineColor(color);
    rectShape.setOutlineThickness(3);
    rectShape.setFillColor(sf::Color(0, 0, 0, 0));
    rectShape.setSize(sf::Vector2f(rect.width, rect.height));
    rectShape.setPosition(sf::Vector2f(rect.left, rect.top));
    target->draw(rectShape);
}
