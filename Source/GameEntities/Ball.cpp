#include "GameEntities/Ball.h"

#include <TeaTimeEngine/Application.h>	
#include <TeaTimeEngine/Scene.h>

#include "GameEntities/Brick.h"
#include "GameEntities/Paddle.h"

Ball::Ball(float radius, sf::Vector2f initialVelocity) :
  _radius(radius), _velocity(initialVelocity)
{
  _shape.setRadius(_radius);
  _shape.setOrigin(sf::Vector2f(_radius, _radius));
  _shape.setFillColor(sf::Color::White);
}

void Ball::Setup()
{
}

void Ball::Start()
{
  sf::Vector2f windowSize = sf::Vector2f(Application::GetInstance()->
    GetRenderWindow().getSize());

  float wallThickness = 10.0f;
  std::vector<sf::FloatRect> walls = {
    sf::FloatRect(
      { 0.0f, -wallThickness },
      { windowSize.x, wallThickness }), // Top
    sf::FloatRect(
      { 0.0f, windowSize.y },
      { windowSize.x, wallThickness }), // Bottom
    sf::FloatRect(
      { -wallThickness, 0.0f},
      { wallThickness, windowSize.y }), // Left
    sf::FloatRect(
      { windowSize.x, 0.0f},
      { wallThickness, windowSize.y }) // Right
  };

  _collisions = std::make_unique<BallCollisions>();

  auto& scenes = Application::GetInstance()->GetScenes();
  std::shared_ptr<Paddle> paddle;
  for (auto& scene : scenes)
  {
    auto found = scene->FindGameEntityOfType(typeid(Paddle));
    if (found != nullptr)
    {
      paddle = std::static_pointer_cast<Paddle>(found);
      break;
    }
  }

  auto pointerToThis = std::static_pointer_cast<Ball>
    (shared_from_this());

  _collisions->Setup(pointerToThis, paddle, walls);
}

void Ball::Update(const float dt)
{
  if (!_canMove)
  {
    return;
  }

  _shape.move(_velocity * dt);

  _collisions->CheckCollisions();
}

void Ball::Render(sf::RenderWindow& window)
{
  //_collisions->DebugDraw(window);
  window.draw(_shape);
}

void Ball::Destroy()
{
  _collisions->Destroy();
}

void Ball::SetRadius(float radius)
{
  _radius = radius;
  _shape.setRadius(_radius);
  _shape.setOrigin(sf::Vector2f(_radius, _radius));
}