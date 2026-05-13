#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

class Ball;
class Brick;
class Paddle;
class Scene;

class BallCollisions
{
private:
  Ball& _ball;
  std::weak_ptr<Paddle> _paddle;
  std::vector<std::weak_ptr<Brick>> _bricks;
  std::vector<sf::FloatRect> _walls;
  std::vector<sf::RectangleShape> _debugWalls;

public:
  BallCollisions(Ball& ball, std::vector<sf::FloatRect> walls);
  ~BallCollisions() = default;

  void Setup(std::vector<std::shared_ptr<Scene>> scenes);
  void CheckCollisions();
  void DebugDraw(sf::RenderWindow& window);

private:
  void CollideWithBricks();
  void CollideWithPaddle();
  void CollideWithWalls();
};