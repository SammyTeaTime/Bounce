#pragma once

#include <memory>

#include <TeaTimeEngine/Entities/IGameEntity.h>

#include "BallCollisions.h"

class Ball : public IGameEntity
{
  IGAMEENTITY_DECLARATION();

private:
  float _radius;
  sf::CircleShape _shape;
  sf::Vector2f _velocity;
  std::unique_ptr<BallCollisions> _collisions;

  bool _canMove = true;

public:
  Ball(float radius, sf::Vector2f initialVelocity);
  ~Ball() = default;

  void Setup() override;
  void Start() override;
  void Update(const float dt) override;
  void Render(sf::RenderWindow& window) override;
  void Destroy() override;

  sf::Vector2f GetPosition() const override { return _shape.getPosition(); }
  void SetPosition(const sf::Vector2f& position) override 
  { _shape.setPosition(position); }

  float GetRadius() const { return _radius; }
  void SetRadius(float radius);

  sf::Vector2f GetVelocity() const { return _velocity; }
  void SetVelocity(sf::Vector2f velocity) { _velocity = velocity; }

  bool CanMove() const { return _canMove; }
  void SetCanMove(bool canMove) { _canMove = canMove; }

  sf::FloatRect GetBounds() const
  {
    return _shape.getGlobalBounds();
  }
};