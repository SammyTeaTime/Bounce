#include "GameEntities/Brick.h"

#include <TeaTimeEngine/Scene.h>
#include <TeaTimeEngine/Entities/IParticleEffect.h>
#include <TeaTimeEngine/Services/IEventService.h>
#include <TeaTimeEngine/Services/IParticlesService.h>

#include "Events/EventNames.h"
#include "Events/GameEntityDestroyedEvent.h"
#include "Events/NumberChangedEvent.h"

Brick::Brick(
  float width,
  float height,
  sf::Color colour,
  int scoreValue,
  ScenePtr scene,
  std::shared_ptr<IEventService> eventService,
  std::shared_ptr<IParticlesService> particlesService) :
    _width(width),
    _height(height),
    _colour(colour),
    _scoreValue(scoreValue),
    _scene(scene),
    _eventService(eventService),
    _particlesService(particlesService)
{
  _shape.setSize(sf::Vector2f(_width, _height));
  _shape.setOrigin(sf::Vector2f(_width * 0.5f, _height * 0.5f));
  _shape.setFillColor(_colour);
}

void Brick::Setup()
{
}

void Brick::Start()
{
}

void Brick::Update(const float dt)
{
}

void Brick::Render(sf::RenderWindow& window)
{
  window.draw(_shape);
}

void Brick::Destroy()
{
  auto scoredChangedEvent = NumberChangedEvent(
    EventNames::SCORE_CHANGED,
    _scoreValue);
  _eventService->ReceiveEvent(scoredChangedEvent);
  
  auto entityDestroyedEvent = GameEntityDestroyedEvent(
   EventNames::BRICK_DESTROYED,
   shared_from_this());
  _eventService->ReceiveEvent(entityDestroyedEvent);

  //TODO: Pool effects instead of instantiating new ones every time
  auto effect = _particlesService->InstantiateEffect(
    "BrickExplodeParticles",
    *_scene,
    GetPosition(),
    false);
  effect->SetColour(GetColour());
  effect->Play();
}