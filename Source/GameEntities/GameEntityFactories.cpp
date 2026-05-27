#include "GameEntities/GameEntityFactories.h"

#include <plog/Log.h>
#include <TeaTimeEngine/Services/IEventService.h>
#include <TeaTimeEngine/Services/IFontService.h>
#include <TeaTimeEngine/Services/IParticlesService.h>
#include <TeaTimeEngine/Services/ServiceLocator.h>

#include "GameEntities/Ball.h"
#include "GameEntities/Brick.h"
#include "GameEntities/BricksMonitor.h"
#include "GameEntities/GameStateMachine.h"
#include "GameEntities/NumberDisplay.h"
#include "GameEntities/Paddle.h"
#include "GameEntities/TimeTracker.h"

IGameEntityPtr BallFactory::Create(const Json& data, ScenePtr scene)
{
  float radius = data["radius"];
  sf::Vector2f initialVelocity = { data["initialVelocity"]["x"],
    data["initialVelocity"]["y"] };

  std::shared_ptr<Ball> ball = std::make_shared<Ball>(
    radius,
    initialVelocity);
  IGAMEENTITYFACTORY_SET_COMMON_PARAMS(ball, data);
  return ball;
}

IGameEntityPtr BrickFactory::Create(const Json& data, ScenePtr scene)
{
  float width = data["width"];
  float height = data["height"];
  sf::Color colour = sf::Color(
    data["colour"]["r"],
    data["colour"]["g"],
    data["colour"]["b"],
    data["colour"]["a"]);
  int scoreValue = data["scoreValue"];

  auto eventService = ServiceLocator::GetService<IEventService>();
  auto particlesService = ServiceLocator::GetService<IParticlesService>();

  auto brick = std::make_shared<Brick>(
    width,
    height,
    colour,
    scoreValue,
    scene,
    eventService,
    particlesService);
  IGAMEENTITYFACTORY_SET_COMMON_PARAMS(brick, data);
  return brick;
}

IGameEntityPtr BricksMonitorFactory::Create(const Json& data, ScenePtr scene)
{
  auto eventService = ServiceLocator::GetService<IEventService>();

  auto bricksMonitor = std::make_shared<BricksMonitor>(
    eventService,
    scene);
  IGAMEENTITYFACTORY_SET_COMMON_PARAMS(bricksMonitor, data);
  return bricksMonitor;
}

IGameEntityPtr GameStateMachineFactory::Create(const Json& data, ScenePtr scene)
{
  auto eventService = ServiceLocator::GetService<IEventService>();

  auto gameStateMachine = std::make_shared<GameStateMachine>(
    scene,
    eventService);
  IGAMEENTITYFACTORY_SET_COMMON_PARAMS(gameStateMachine, data);
  return gameStateMachine;
}

IGameEntityPtr NumberDisplayFactory::Create(const Json& data, ScenePtr scene)
{
  const std::string font = "font";
  const std::string label = "label";
  const std::string numberFormat = "numberFormat";
  const std::string numberChangedEventName = "numberChangedEventName";

  if (!data.contains(font) || !data[font].is_string())
  {
    PLOG_ERROR << "NumberDisplayFactory: Missing or invalid 'font' parameter";
    throw std::runtime_error("NumberDisplayFactory: Missing or invalid 'font' "
      "parameter");
  }

  std::string fontName = data[font];

  auto fontService = ServiceLocator::GetService<IFontService>();
  if (!fontService)
  {
    PLOG_ERROR << "NumberDisplayFactory: FontService not available";
    throw std::runtime_error("NumberDisplayFactory: FontService not available to "
      "retrieve fonts");
  }

  const sf::Font& fontObject = fontService->GetFont(fontName);

  std::string labelString = "";
  if (data.contains(label) && data[label].is_string())
  {
    labelString = data[label];
  }

  std::string numberFormatString = "";
  if (data.contains(numberFormat) && data[numberFormat].is_string())
  {
    numberFormatString = data[numberFormat];
  }

  std::string numberChangeEventNameString = "";
  if (data.contains(numberChangedEventName) && 
    data[numberChangedEventName].is_string())
  {
    numberChangeEventNameString = data[numberChangedEventName];
  }

  auto eventService = ServiceLocator::GetService<IEventService>();

  auto numberDisplay = std::make_shared<NumberDisplay>(
    fontObject,
    labelString,
    numberFormatString,
    numberChangeEventNameString,
    eventService);
  IGAMEENTITYFACTORY_SET_COMMON_PARAMS(numberDisplay, data);
  return numberDisplay;
}

IGameEntityPtr PaddleFactory::Create(const Json& data, ScenePtr scene)
{
  int numSections = data["numSections"];
  int sectionWidth = data["sectionWidth"];
  int sectionHeight = data["sectionHeight"];
  float movementSpeed = data["movementSpeed"];

  std::shared_ptr<Paddle> paddle = std::make_shared<Paddle>(
    numSections,
    sectionWidth,
    sectionHeight,
    movementSpeed);
  IGAMEENTITYFACTORY_SET_COMMON_PARAMS(paddle, data);
  return paddle;
}

IGameEntityPtr TimeTrackerFactory::Create(const Json& data, ScenePtr scene)
{
  const std::string timeChangedEventName = "timeChangedEventName";

  std::string timeChangedEventNameString = "";
  if (data.contains(timeChangedEventName) &&
    data[timeChangedEventName].is_string())
  {
    timeChangedEventNameString = data[timeChangedEventName];
  }

  auto eventService = ServiceLocator::GetService<IEventService>();

  std::shared_ptr<TimeTracker> timeTracker = std::make_shared<TimeTracker>(
    timeChangedEventNameString,
    eventService);
  IGAMEENTITYFACTORY_SET_COMMON_PARAMS(timeTracker, data);
  return timeTracker;
}