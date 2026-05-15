#include "GameEntities/TimeTracker.h"

#include <TeaTimeEngine/Services/IEventService.h>

#include "Events/NumberChangedEvent.h"

TimeTracker::TimeTracker(
  const std::string timerChangedEventName,
  std::shared_ptr<IEventService> eventService) : 
    _timeChangedEventName(timerChangedEventName),
    _eventService(eventService)
{
}

void TimeTracker::Setup() {}

void TimeTracker::Start() {}

void TimeTracker::Update(const float dt)
{
  if (_isPaused)
  {
    return;
  }

  auto event = NumberChangedEvent(_timeChangedEventName, dt);

  _eventService->ReceiveEvent(event);

  _elapsedSeconds += dt;
}

void TimeTracker::Render(sf::RenderWindow& window) {}

void TimeTracker::Destroy() {}

void TimeTracker::PauseTimer()
{
  _isPaused = true;
}

void TimeTracker::ClearTimer()
{
  auto event = NumberChangedEvent(
    _timeChangedEventName, 
    _elapsedSeconds * -1.0);

  _eventService->ReceiveEvent(event);

  _elapsedSeconds = 0.0;
}

void TimeTracker::StartTimer()
{
  _isPaused = false;
}