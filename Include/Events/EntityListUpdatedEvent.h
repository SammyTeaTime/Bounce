#pragma once

#include <memory>
#include <vector>

#include <TeaTimeEngine/Entities/IGameEntity.h>
#include <TeaTimeEngine/Events/IEvent.h>

class EntityListUpdatedEvent : public IEvent
{
private:
  std::string _eventName;
  EntityListPtr _entities;

public:
  EntityListUpdatedEvent(const std::string& eventName, EntityListPtr entities) 
    : _eventName(eventName), _entities(entities) {}
  ~EntityListUpdatedEvent() = default;

  std::string GetName() const override
  {
    return _eventName;
  }

  EntityListPtr GetEntityList() const { return _entities; }
};