#pragma once

#include <string>

#include <TeaTimeEngine/Entities/IGameEntity.h>

class IEventService;

class TimeTracker : public IGameEntity
{
  IGAMEENTITY_DECLARATION();

private:
  std::string _timeChangedEventName;
  std::shared_ptr<IEventService> _eventService;

  double _elapsedSeconds = 0.0;
  bool _isPaused = false;

public:
  TimeTracker(
    const std::string timeChangedEventName,
    std::shared_ptr<IEventService> eventService);
  ~TimeTracker() = default;

  void Setup() override;
  void Start() override;
  void Update(const float dt) override;
  void Render(sf::RenderWindow& window) override;
  void Destroy() override;

  void PauseTimer();
  void ClearTimer();
  void StartTimer();

  sf::Vector2f GetPosition() const override { return {0.0f, 0.0f}; }
  void SetPosition(const sf::Vector2f& position) override {}
};