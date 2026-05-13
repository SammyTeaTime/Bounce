#pragma once

#include <TeaTimeEngine/Entities/IGameEntity.h>

class Brick : public IGameEntity
{
private:
  float _width;
  float _height;
  sf::Color _colour;
  sf::RectangleShape _shape;

public:
  Brick(float width, float height, sf::Color colour);
  ~Brick() = default;

  void Setup() override;
  void Start() override;
  void Update(const float dt) override;
  void Render(sf::RenderWindow& window) override;
  void Destroy() override;

  sf::Vector2f GetPosition() const override { return _shape.getPosition(); }
  void SetPosition(const sf::Vector2f& position) override 
  { _shape.setPosition(position); }

  sf::Color GetColour() const { return _colour; }

  sf::FloatRect GetBounds() const
  {
    return _shape.getGlobalBounds();
  }
};