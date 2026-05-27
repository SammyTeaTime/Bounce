#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include <TeaTimeEngine/Events/EventListener.h>

class Ball;
class Brick;
class IGameEntity;
class Paddle;
class Scene;

typedef std::shared_ptr<IGameEntity> IGameEntityPtr;
typedef std::vector<IGameEntityPtr> EntityList;
typedef std::shared_ptr<EntityList> EntityListPtr;

class BallCollisions : public EventListener
{
private:
  std::weak_ptr<Ball> _ball;
  std::weak_ptr<Paddle> _paddle;
  std::vector<sf::FloatRect> _walls;
  std::vector<sf::RectangleShape> _debugWalls;
  EntityListPtr _bricks;

public:
  BallCollisions() = default;
  ~BallCollisions() = default;

  void Setup(
    std::shared_ptr<Ball> ball, 
    std::shared_ptr<Paddle> paddle, 
    std::vector<sf::FloatRect> walls);
  void Destroy();
  void CheckCollisions();
  void DebugDraw(sf::RenderWindow& window);

  void OnEventTriggered(const IEvent& event) override;

private:
  void CollideWithBricks();
  void CollideWithPaddle();
  void CollideWithWalls();
};