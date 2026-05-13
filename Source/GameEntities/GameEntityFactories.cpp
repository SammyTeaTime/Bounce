#include "GameEntities/GameEntityFactories.h"

#include <plog/Log.h>

#include "GameEntities/Ball.h"
#include "GameEntities/Brick.h"
#include "GameEntities/Paddle.h"

IGameEntityPtr BallFactory::Create(const Json& data)
{
  float radius = data["radius"];
  sf::Vector2f initialVelocity = { data["initialVelocity"]["x"],
    data["initialVelocity"]["y"] };

  std::shared_ptr<Ball> ball = std::make_shared<Ball>(radius,
    initialVelocity);

  IGameEntityFactory::ParseAndSetCommonParams(ball, data);

  return ball;
}

IGameEntityPtr BrickFactory::Create(const Json& data)
{
  float width = data["width"];
  float height = data["height"];
  sf::Color colour = sf::Color(
    data["colour"]["r"],
    data["colour"]["g"],
    data["colour"]["b"],
    data["colour"]["a"]);

  std::shared_ptr<Brick> brick = std::make_shared<Brick>(width, height,
    colour);

  IGameEntityFactory::ParseAndSetCommonParams(brick, data);

  return brick;
}

IGameEntityPtr PaddleFactory::Create(const Json& data)
{
  int numSections = data["numSections"];
  int sectionWidth = data["sectionWidth"];
  int sectionHeight = data["sectionHeight"];
  float movementSpeed = data["movementSpeed"];

  std::shared_ptr<Paddle> paddle = std::make_shared<Paddle>(numSections,
    sectionWidth, sectionHeight, movementSpeed);

  IGameEntityFactory::ParseAndSetCommonParams(paddle, data);

  return paddle;
}