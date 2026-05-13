#include <SFML/Graphics.hpp>
#include <TeaTimeEngine/Application.h>

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
  sf::Vector2f position = GetPosition();
  sf::Vector2f paddleSize = CalculatePaddleSize();
  
  return sf::FloatRect(
    { position.x - paddleSize.x * 0.5f, position.y - paddleSize.y * 0.5f },
    { paddleSize.x, paddleSize.y });
}

void Paddle::Setup()
{
  _windowSize = Application::GetInstance()->GetRenderWindow().getSize();
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

  CollideWithWalls();
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
  sf::Vector2f position = GetPosition();

  for (int i = 0; i < _numSections; ++i)
  {
    _paddleSections[i].setPosition({ position.x +
      _sectionWidth * 0.5f + paddleWidth * -0.5f + i * _sectionWidth,
      position.y });
  }
}

void Paddle::CollideWithWalls()
{
  sf::Vector2f paddleSize = CalculatePaddleSize();
  sf::Vector2f position = GetPosition();
  float minX = position.x - paddleSize.x * 0.5f;
  float maxX = position.x + paddleSize.x * 0.5f;

  if (minX < 0)
  {
    SetPosition(sf::Vector2f(
      paddleSize.x * 0.5f,
      position.y));
  }
  else if (maxX > _windowSize.x)
  {
    SetPosition(sf::Vector2f(
      _windowSize.x - paddleSize.x * 0.5f,
      position.y));
  }
}

sf::Vector2f Paddle::CalculatePaddleSize() const
{
  return sf::Vector2f((float)_numSections * _sectionWidth, (float)_sectionHeight);
}