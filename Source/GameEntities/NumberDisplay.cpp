#include "GameEntities/NumberDisplay.h"

#include <format>

#include <TeaTimeEngine/Services/IEventService.h>

#include "Events/NumberChangedEvent.h"

NumberDisplay::NumberDisplay(
  const sf::Font& font,
  const std::string& label,
  const std::string& numberFormat,
  const std::string& numberChangedEventName,
  std::shared_ptr<IEventService> eventService) :
    TextEntity(font, ""),
    _label(label),
    _numberFormat(numberFormat),
  _numberChangedEventName(numberChangedEventName),
    _eventService(eventService)
{
  _eventService->RegisterListener(_numberChangedEventName, this);
}

void NumberDisplay::Setup()
{
  TextEntity::Setup();
}

void NumberDisplay::Start()
{
  TextEntity::Start();

  UpdateDisplayedNumber();
}

void NumberDisplay::Update(const float dt)
{
  TextEntity::Update(dt);

  if (_displayedNumber != _number)
  {
    _displayedNumber = _number;
    UpdateDisplayedNumber();
  }
}

void NumberDisplay::Render(sf::RenderWindow& window)
{
  TextEntity::Render(window);
}

void NumberDisplay::Destroy()
{
  TextEntity::Destroy();

  _eventService->UnregisterListener(_numberChangedEventName, this);
}

void NumberDisplay::OnEventTriggered(const IEvent& event)
{
  if (event.GetName() != _numberChangedEventName)
  {
    return;
  }

  auto& numberChangedEvent = static_cast<const NumberChangedEvent&>(event);
  _number += numberChangedEvent.GetNumberDelta();
}

void NumberDisplay::UpdateDisplayedNumber()
{
  auto formattedNumber = std::vformat(_numberFormat, 
    std::make_format_args(_displayedNumber));

  _sfText.setString(_label + formattedNumber);
}