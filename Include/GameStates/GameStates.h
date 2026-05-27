#pragma once

#include <memory>
#include <vector>

#include <TeaTimeEngine/Events/EventListener.h>

#include "GameStates/IGameState.h"

class Brick;
class IEventService;
class GameStateMachine;
typedef std::shared_ptr<GameStateMachine> GameStateMachinePtr;
class Scene;
typedef std::shared_ptr<Scene> ScenePtr;

class GameplayState : public IGameState, public EventListener
{
private:
  GameStateMachinePtr _stateMachine;
  std::shared_ptr<IEventService> _eventService;

  bool _isComplete = false;

public:
  GameplayState(
    GameStateMachinePtr stateMachine,
    std::shared_ptr<IEventService> eventService);
  ~GameplayState() = default;

  void OnEnter() override;
  void OnExit() override;
  std::unique_ptr<IGameState> Update(float dt) override;

  void OnEventTriggered(const IEvent& event) override;
};

class GameFinishedState : public IGameState
{
private:
  GameStateMachinePtr _stateMachine;
  ScenePtr _scene;

public:
  GameFinishedState(
    GameStateMachinePtr stateMachine, 
    ScenePtr scene);
  ~GameFinishedState() = default;

  void OnEnter() override;
  void OnExit() override;
  std::unique_ptr<IGameState> Update(float dt) override;
};