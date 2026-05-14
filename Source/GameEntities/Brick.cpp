#include "GameEntities/Brick.h"

#include <TeaTimeEngine/Services/IEventService.h>

#include "Events/BrickDestroyedEvent.h"

Brick::Brick(float width, float height, sf::Color colour, int scoreValue,
  std::shared_ptr<IEventService> eventService) :
  _width(width), _height(height), _colour(colour), _scoreValue(scoreValue), 
  _eventService(eventService)
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
  auto event = BrickDestroyedEvent(_scoreValue);
  _eventService->ReceiveEvent(event);
}