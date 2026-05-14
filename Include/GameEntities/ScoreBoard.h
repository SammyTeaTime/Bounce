#pragma once

#include <memory>

#include <TeaTimeEngine/Entities/TextEntity.h>
#include <TeaTimeEngine/Events/EventListener.h>

class IEventService;

class ScoreBoard : public TextEntity, EventListener
{
private:
  int _score = 0;
  int _displayedScore = 0;
  std::shared_ptr<IEventService> _eventService;

public:
  ScoreBoard(const sf::Font& font, const std::string& text,
    std::shared_ptr<IEventService> eventService);
  ~ScoreBoard() = default;

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
  void UpdateDisplayedScore();
};