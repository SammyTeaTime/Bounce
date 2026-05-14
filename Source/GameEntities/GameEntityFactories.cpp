#include "GameEntities/GameEntityFactories.h"

#include <plog/Log.h>
#include <TeaTimeEngine/Services/IEventService.h>
#include <TeaTimeEngine/Services/IFontService.h>
#include <TeaTimeEngine/Services/ServiceLocator.h>

#include "GameEntities/Ball.h"
#include "GameEntities/Brick.h"
#include "GameEntities/Paddle.h"
#include "GameEntities/Scoreboard.h"

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
  int scoreValue = data["scoreValue"];

  auto eventService = ServiceLocator::GetInstance()->
    GetService<IEventService>();

  std::shared_ptr<Brick> brick = std::make_shared<Brick>(width, height,
    colour, scoreValue, eventService);

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

IGameEntityPtr ScoreBoardFactory::Create(const Json& data)
{
  if (!data.contains("font") || !data["font"].is_string())
  {
    PLOG_ERROR << "ScoreBoardFactory: Missing or invalid 'font' parameter";
    throw std::runtime_error("ScoreBoardFactory: Missing or invalid 'font' "
      "parameter");
  }

  std::string fontName = data["font"];

  auto fontService = ServiceLocator::GetInstance()->GetService<IFontService>();
  if (!fontService)
  {
    PLOG_ERROR << "ScoreBoardFactory: FontService not available";
    throw std::runtime_error("ScoreBoardFactory: FontService not available to "
      "retrieve fonts");
  }

  const sf::Font& font = fontService->GetFont(fontName);

  std::string text = "";
  if (data.contains("text") && data["text"].is_string())
  {
    text = data["text"];
  }

  auto eventService = ServiceLocator::GetInstance()->
    GetService<IEventService>();

  auto scoreBoard = std::make_shared<ScoreBoard>(font, text, eventService);
  IGameEntityFactory::ParseAndSetCommonParams(scoreBoard, data);
  return scoreBoard;
}