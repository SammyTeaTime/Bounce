#pragma once

#include <memory>

#include <TeaTimeEngine/Entities/TextEntity.h>
#include <TeaTimeEngine/Events/EventListener.h>

class IEventService;

class NumberDisplay : public TextEntity, EventListener
{
  IGAMEENTITY_DECLARATION();

private:
  double _number = 0.0;
  double _displayedNumber = 0.0;
  std::string _label;
  std::string _numberFormat;
  std::string _numberChangedEventName;
  std::shared_ptr<IEventService> _eventService;

public:
  NumberDisplay(
    const sf::Font& font,
    const std::string& label,
    const std::string& numberFormat,
    const std::string& numberChangedEventName,
    std::shared_ptr<IEventService> eventService);
  ~NumberDisplay() = default;

  void Setup() override;
  void Start() override;
  void Update(const float dt) override;
  void Render(sf::RenderWindow& window) override;
  void Destroy() override;

  sf::Vector2f GetPosition() const override 
  { 
    return TextEntity::GetPosition();
  }
  void SetPosition(const sf::Vector2f& position) override 
  { 
    TextEntity::SetPosition(position);
  }

  void OnEventTriggered(const IEvent& event) override;

private:
  void UpdateDisplayedNumber();
};