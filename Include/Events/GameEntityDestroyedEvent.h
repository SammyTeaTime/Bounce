#pragma once

#include <memory>

#include <TeaTimeEngine/Events/IEvent.h>

class IGameEntity;

class GameEntityDestroyedEvent : public IEvent
{
private:
  std::string _eventName;
  std::shared_ptr<IGameEntity> _gameEntity;

public:
  GameEntityDestroyedEvent(
    const std::string& eventName,
    std::shared_ptr<IGameEntity> gameEntity) :
      _eventName(eventName),
    _gameEntity(gameEntity) {}
  ~GameEntityDestroyedEvent() = default;

  std::string GetName() const override
  {
    return _eventName;
  }

  std::shared_ptr<IGameEntity> GetGameEntity() const { return _gameEntity; }
};