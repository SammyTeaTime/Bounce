#pragma once

#include <SFML/Graphics.hpp>
#include <TeaTimeEngine/Entities/IGameEntity.h>

class Paddle : public IGameEntity
{
private:
  sf::Transformable _transform;
  sf::RectangleShape* _paddleSections;

  int _numSections;
  int _sectionWidth;
  int _sectionHeight;
  float _movementSpeed;

public:
  Paddle(int numSections, int sectionWidth, int sectionHeight,
    float movementSpeed);
  ~Paddle() = default;
  
  void Move(sf::Vector2f offset);
  sf::FloatRect GetBounds() const;

  void Setup() override;
  void Start() override;
  void Update(const float dt) override;
  void Render(sf::RenderWindow& window) override;
  void Destroy();

  sf::Vector2f GetPosition() const override
  { return _transform.getPosition(); }
  void SetPosition(const sf::Vector2f& position) override;

private:
  void LayoutSections();
};