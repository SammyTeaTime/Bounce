#include "GameEntities/BallCollisions.h"

#include <TeaTimeEngine/Application.h>
#include <TeaTimeEngine/Events/GenericEvent.h>
#include <TeaTimeEngine/Services/IEventService.h>

#include "Events/EntityListUpdatedEvent.h"
#include "Events/EventNames.h"
#include "GameEntities/Ball.h"
#include "GameEntities/Brick.h"
#include "GameEntities/Paddle.h"

void BallCollisions::Setup(
  std::shared_ptr<Ball> ball,
  std::shared_ptr<Paddle> paddle,
  std::vector<sf::FloatRect> walls)
{
  _ball = ball;
  _paddle = paddle;
  _walls = walls;

  for (auto& wall : _walls)
  {
    sf::RectangleShape debugWall;
    debugWall.setPosition(wall.position);
    debugWall.setSize(wall.size);
    debugWall.setFillColor(sf::Color::Transparent);
    debugWall.setOutlineColor(sf::Color(255, 0, 0, 128));
    debugWall.setOutlineThickness(1.0f);
    _debugWalls.push_back(debugWall);
  }

  auto eventService = ServiceLocator::GetService<IEventService>();

  eventService->RegisterListener(EventNames::BRICKS_UPDATED, this);

  auto requestBricksUpdateEvent = 
    GenericEvent(EventNames::REQUEST_BRICKS_UPDATE);
  eventService->ReceiveEvent(requestBricksUpdateEvent);
}

void BallCollisions::Destroy()
{
  auto eventService = ServiceLocator::GetService<IEventService>();

  eventService->UnregisterListener(EventNames::BRICKS_UPDATED, this);
}

void BallCollisions::CheckCollisions()
{
  CollideWithPaddle();
  CollideWithBricks();
  CollideWithWalls();
}

void BallCollisions::DebugDraw(sf::RenderWindow& window)
{
  for (const sf::RectangleShape& debugWall : _debugWalls)
  {
    window.draw(debugWall);
  }
}

void BallCollisions::OnEventTriggered(const IEvent& event)
{
  if (event.GetName() != EventNames::BRICKS_UPDATED)
  {
    return;
  }

  auto& entityListUpdatedEvent = 
    static_cast<const EntityListUpdatedEvent&>(event);
  _bricks = entityListUpdatedEvent.GetEntityList();
}

void BallCollisions::CollideWithBricks()
{
  auto& ball = *(_ball.lock());

  sf::FloatRect ballBounds = ball.GetBounds();

  std::vector<std::weak_ptr<Brick>> destroyedBricks;

  for (auto& entity : *_bricks)
  {
    auto brick = std::static_pointer_cast<Brick>(entity);
    sf::FloatRect brickBounds = brick->GetBounds();
    if (!ballBounds.findIntersection(brickBounds))
    {
      continue;
    }

    ball.SetVelocity({ ball.GetVelocity().x, -ball.GetVelocity().y });

    destroyedBricks.push_back(brick);
  }

  for (auto& destroyedBrick : destroyedBricks)
  {
    auto& scenes = Application::GetInstance()->GetScenes();
    for (auto& scene : scenes)
    {
      scene->RemoveGameEntity(destroyedBrick.lock());
    }
  }
}

void BallCollisions::CollideWithPaddle()
{
  auto& ball = *(_ball.lock());
  auto& paddle = *(_paddle.lock());

  sf::FloatRect ballBounds = ball.GetBounds();
  sf::FloatRect paddleBounds = paddle.GetBounds();
  if (ballBounds.findIntersection(paddleBounds))
  {
    ball.SetVelocity(
      {
        ball.GetVelocity().x,
        -ball.GetVelocity().y
      });
  }
}

void BallCollisions::CollideWithWalls()
{
  auto& ball = *(_ball.lock());

  sf::FloatRect ballBounds = ball.GetBounds();
  for (const sf::FloatRect& wall : _walls)
  {
    if (ballBounds.findIntersection(wall))
    {
      if (ballBounds.position.x < wall.position.x ||
        ballBounds.position.x + ballBounds.size.x >
        wall.position.x + wall.size.x)
      {
        ball.SetVelocity(
          {
            -ball.GetVelocity().x,
            ball.GetVelocity().y
          });
      }
      else
      {
        ball.SetVelocity(
          {
            ball.GetVelocity().x,
            -ball.GetVelocity().y
          });
      }
    }
  }
}