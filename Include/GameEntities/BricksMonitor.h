#pragma once

#include <memory>

#include <TeaTimeEngine/Entities/IGameEntity.h>
#include <TeaTimeEngine/Events/EventListener.h>

class Brick;
class IEventService;
class Scene;
typedef std::shared_ptr<Scene> ScenePtr;

class BricksMonitor : public IGameEntity, public EventListener
{
  IGAMEENTITY_DECLARATION();

private:
  std::shared_ptr<IEventService> _eventService;
  ScenePtr _scene;
  EntityListPtr _bricks;

public:
  BricksMonitor(
    std::shared_ptr<IEventService> eventService,
    ScenePtr scene) : 
      _eventService(eventService),
      _scene(scene), 
      _bricks(nullptr) {}
  ~BricksMonitor() = default;

  void Setup() override;
  void Start() override;
  void Update(const float dt) override;
  void Render(sf::RenderWindow& window) override;
  void Destroy() override;

  sf::Vector2f GetPosition() const override { return { 0.0f, 0.0f }; }
  void SetPosition(const sf::Vector2f& position) override {}

  void OnEventTriggered(const IEvent& event) override;

private:
  void SendBricksUpdatedEvent() const;
};