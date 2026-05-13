#include "GameEntities/Brick.h"

Brick::Brick(float width, float height, sf::Color colour) :
  _width(width), _height(height), _colour(colour)
{
  _shape.setSize(sf::Vector2f(_width, _height));
  _shape.setOrigin(sf::Vector2f(_width * 0.5f, _height * 0.5f));
  _shape.setFillColor(_colour);
}

void Brick::Setup()
{
}

void Brick::Start()
{
}

void Brick::Update(const float dt)
{
}

void Brick::Render(sf::RenderWindow& window)
{
  window.draw(_shape);
}

void Brick::Destroy()
{
}