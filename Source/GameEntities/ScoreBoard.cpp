#include "GameEntities/ScoreBoard.h"

#include <TeaTimeEngine/Services/IEventService.h>

#include "Events/BrickDestroyedEvent.h"

ScoreBoard::ScoreBoard(const sf::Font& font, const std::string& text, 
  std::shared_ptr<IEventService> eventService) :
  TextEntity(font, text), _eventService(eventService)
{
  _eventService->RegisterListener(BrickDestroyedEvent::EVENT_NAME, this);
}

void ScoreBoard::Setup()
{
  TextEntity::Setup();
}

void ScoreBoard::Start()
{
  TextEntity::Start();

  UpdateDisplayedScore();
}

void ScoreBoard::Update(const float dt)
{
  TextEntity::Update(dt);

  if (_displayedScore != _score)
  {
    _displayedScore = _score;
    UpdateDisplayedScore();
  }
}

void ScoreBoard::Render(sf::RenderWindow& window)
{
  TextEntity::Render(window);
}

void ScoreBoard::Destroy()
{
  TextEntity::Destroy();

  _eventService->UnregisterListener(BrickDestroyedEvent::EVENT_NAME, this);
}

void ScoreBoard::OnEventTriggered(const IEvent& event)
{
  if (event.GetName() != BrickDestroyedEvent::EVENT_NAME)
  {
    return;
  }

  auto& brickDestroyedEvent = static_cast<const BrickDestroyedEvent&>(event);
  _score += brickDestroyedEvent.GetScoreAwarded();
}

void ScoreBoard::UpdateDisplayedScore()
{
  _sfText.setString("Score: " + std::to_string(_displayedScore));
}