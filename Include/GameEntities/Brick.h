#pragma once

#include <memory>

#include <TeaTimeEngine/Entities/IGameEntity.h>

class IEventService;

class Brick : public IGameEntity
{
  IGAMEENTITY_DECLARATION();

private:
  float _width;
  float _height;
  sf::Color _colour;
  int _scoreValue;
  sf::RectangleShape _shape;

  std::shared_ptr<IEventService> _eventService;

public:
  Brick(float width, float height, sf::Color colour, int scoreValue,
    std::shared_ptr<IEventService>);
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