#include <SFML/Graphics.hpp>

#include "GameEntities/Paddle.h"

Paddle::Paddle(int numSections, int sectionWidth, int sectionHeight,
  float movementSpeed) :
  _numSections(numSections),
  _sectionWidth(sectionWidth),
  _sectionHeight(sectionHeight),
  _movementSpeed(movementSpeed)
{
  _paddleSections = new sf::RectangleShape[_numSections];

  for (int i = 0; i < _numSections; ++i)
  {
    _paddleSections[i].setSize(sf::Vector2f((float)_sectionWidth,
      (float)sectionHeight));
    _paddleSections[i].setOrigin(sf::Vector2f((float)_sectionWidth * 0.5f,
      (float)_sectionHeight * 0.5f));
    _paddleSections[i].setFillColor(sf::Color::White);
  }

  _transform.setOrigin(sf::Vector2f((_numSections * _sectionWidth) * 0.5f,
    _sectionHeight * 0.5f));
}

void Paddle::SetPosition(const sf::Vector2f& position)
{
  _transform.setPosition(position);
  LayoutSections();
}

void Paddle::Move(sf::Vector2f offset)
{
  _transform.move(offset);
  LayoutSections();
}

sf::FloatRect Paddle::GetBounds() const
{
  float paddleWidth = (float)_numSections * _sectionWidth;
  return sf::FloatRect(
    { _transform.getPosition().x - paddleWidth * 0.5f,
    _transform.getPosition().y - (float)_sectionHeight * 0.5f },
    { paddleWidth, (float)_sectionHeight });
}

void Paddle::Setup()
{
}

void Paddle::Start()
{
}

void Paddle::Update(const float dt)
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
  {
    Move({ -_movementSpeed * dt, 0.0f });
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
  {
    Move({ _movementSpeed * dt, 0.0f });
  }
}

void Paddle::Render(sf::RenderWindow& window)
{
  for (int i = 0; i < _numSections; ++i)
  {
    window.draw(_paddleSections[i]);
  }
}

void Paddle::Destroy()
{
  delete[] _paddleSections;
  _paddleSections = nullptr;
}

void Paddle::LayoutSections()
{
  float paddleWidth = (float)_numSections * _sectionWidth;

  for (int i = 0; i < _numSections; ++i)
  {
    _paddleSections[i].setPosition({ _transform.getPosition().x +
      _sectionWidth * 0.5f + paddleWidth * -0.5f + i * _sectionWidth,
      _transform.getPosition().y });
  }
}