#pragma once

#include <TeaTimeEngine/Events/IEvent.h>

class NumberChangedEvent : public IEvent
{
private:
  std::string _eventName;
  double _numberDelta = 0;

public:
  NumberChangedEvent(
    const std::string& eventName, 
    double numberDelta) : 
      _eventName(eventName),
      _numberDelta(numberDelta) {}
  ~NumberChangedEvent() = default;

  std::string GetName() const override 
  { 
    return _eventName;
  }

  double GetNumberDelta() const { return _numberDelta;  }
};