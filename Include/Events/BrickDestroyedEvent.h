#pragma once

#include <TeaTimeEngine/Events/IEvent.h>

class BrickDestroyedEvent : public IEvent
{
public:
  inline static const std::string EVENT_NAME = "BrickDestroyed";

private:
  int _scoreAwarded = 0;

public:
  BrickDestroyedEvent(int scoreAwarded) : _scoreAwarded(scoreAwarded) {}
  ~BrickDestroyedEvent() = default;

  std::string GetName() const override 
  { 
    return BrickDestroyedEvent::EVENT_NAME; 
  }

  int GetScoreAwarded() const { return _scoreAwarded;  }
};