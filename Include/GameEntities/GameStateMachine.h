#pragma once

#include <memory>

#include <TeaTimeEngine/Entities/IGameEntity.h>

#include "GameStates/IGameState.h"

class IEventService;
class Scene;
typedef std::shared_ptr<Scene> ScenePtr;

class GameStateMachine : public IGameEntity
{
  IGAMEENTITY_DECLARATION();

private:
  std::unique_ptr<IGameState> _state = nullptr;
  std::shared_ptr<IEventService> _eventService;
  ScenePtr _scene;

public:
  GameStateMachine(
    ScenePtr scene, 
    std::shared_ptr<IEventService> eventService) :
      _scene(scene),
      _eventService(eventService) {}
  ~GameStateMachine() = default;

  void Setup() override;
  void Start() override;
  void Update(const float dt) override;
  void Render(sf::RenderWindow& window) override;
  void Destroy() override;

  sf::Vector2f GetPosition() const override { return { 0.0f, 0.0f }; }
  void SetPosition(const sf::Vector2f& position) override {}

  ScenePtr GetScene() const { return _scene; }
};