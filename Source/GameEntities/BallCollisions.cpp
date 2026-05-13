#include "GameEntities/BallCollisions.h"

#include <TeaTimeEngine/Application.h>
#include <TeaTimeEngine/Entities/IParticleEffect.h>
#include <TeaTimeEngine/Scene.h>
#include <TeaTimeEngine/Services/IParticleEffectService.h>

#include "GameEntities/Ball.h"
#include "GameEntities/Brick.h"
#include "GameEntities/Paddle.h"

BallCollisions::BallCollisions(Ball& ball, std::vector<sf::FloatRect> walls) :
  _ball(ball), _walls(walls)
{
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
}

void BallCollisions::Setup(std::vector<std::shared_ptr<Scene>> scenes)
{
  for (auto& scene : scenes)
  {
    auto entity = scene->FindGameEntityOfType(typeid(Paddle));
    if (entity != nullptr)
    {
      _paddle = std::dynamic_pointer_cast<Paddle>(entity);
      break;
    }
  }

  if (_paddle.expired())
  {
    throw std::runtime_error("BallCollisions requires a Paddle entity in the scene");
    return;
  }

  for (auto& scene : scenes)
  {
    std::vector<IGameEntityPtr> brickEntities =
      scene->FindGameEntitiesOfType(typeid(Brick));

    for (auto& brickEntity : brickEntities)
    {
      std::shared_ptr<Brick> brick =
        std::dynamic_pointer_cast<Brick>(brickEntity);
      if (brick != nullptr)
      {
        _bricks.push_back(std::weak_ptr<Brick>(brick));
      }
    }
  }
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

void BallCollisions::CollideWithBricks()
{
  sf::FloatRect ballBounds = _ball.GetBounds();

  std::vector<std::weak_ptr<Brick>> destroyedBricks;

  for (auto& brick : _bricks)
  {
    sf::FloatRect brickBounds = brick.lock()->GetBounds();
    if (!ballBounds.findIntersection(brickBounds))
    {
      continue;
    }

    _ball.SetVelocity({ _ball.GetVelocity().x, -_ball.GetVelocity().y });

    auto particleEffectService = ServiceLocator::GetInstance()->
      GetService<IParticleEffectService>();
    //TODO: Pool effects instead of instantiating new ones every time
    auto effect = particleEffectService->InstantiateEffect(
      "BrickExplodeParticles",
      *Application::GetInstance()->GetScenes().front(),
      brick.lock()->GetPosition(),
      false);
    effect->SetColour(brick.lock()->GetColour());
    effect->Play();

    destroyedBricks.push_back(brick);
  }

  for (auto& destroyedBrick : destroyedBricks)
  {
    auto& scenes = Application::GetInstance()->GetScenes();
    for (auto& scene : scenes)
    {
      scene->RemoveGameEntity(destroyedBrick.lock());
    }

    _bricks.erase(std::remove_if(_bricks.begin(), _bricks.end(),
      [&destroyedBrick](const std::weak_ptr<Brick>& wp)
      {
        return !(wp.owner_before(destroyedBrick) ||
          destroyedBrick.owner_before(wp));
      }), _bricks.end());
  }
}

void BallCollisions::CollideWithPaddle()
{
  sf::FloatRect ballBounds = _ball.GetBounds();
  sf::FloatRect paddleBounds = _paddle.lock()->GetBounds();
  if (ballBounds.findIntersection(paddleBounds))
  {
    _ball.SetVelocity(
      {
        _ball.GetVelocity().x,
        -_ball.GetVelocity().y
      });
  }
}

void BallCollisions::CollideWithWalls()
{
  sf::FloatRect ballBounds = _ball.GetBounds();
  for (const sf::FloatRect& wall : _walls)
  {
    if (ballBounds.findIntersection(wall))
    {
      if (ballBounds.position.x < wall.position.x ||
        ballBounds.position.x + ballBounds.size.x >
        wall.position.x + wall.size.x)
      {
        _ball.SetVelocity(
          {
            -_ball.GetVelocity().x,
            _ball.GetVelocity().y
          });
      }
      else
      {
        _ball.SetVelocity(
          {
            _ball.GetVelocity().x,
            -_ball.GetVelocity().y
          });
      }
    }
  }
}