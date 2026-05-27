#include "GameStates/GameStates.h"

#include <TeaTimeEngine/Application.h>
#include <TeaTimeEngine/Scene.h>
#include <TeaTimeEngine/Services/IEventService.h>

#include "Events/EventNames.h"
#include "GameEntities/Ball.h"
#include "GameEntities/Brick.h"
#include "GameEntities/GameStateMachine.h"
#include "GameEntities/Paddle.h"
#include "GameEntities/TimeTracker.h"

GameplayState::GameplayState(
  std::shared_ptr<GameStateMachine> stateMachine,
  std::shared_ptr<IEventService> eventService) : 
    _stateMachine(stateMachine),
    _eventService(eventService)
{
}

void GameplayState::OnEnter()
{
  _eventService->RegisterListener(EventNames::ALL_BRICKS_DESTROYED, this);
}

void GameplayState::OnExit()
{
  _eventService->UnregisterListener(EventNames::ALL_BRICKS_DESTROYED, this);
}

std::unique_ptr<IGameState> GameplayState::Update(float dt)
{
  if (_isComplete)
  {
    auto gameFinishedState = std::make_unique<GameFinishedState>(
      _stateMachine,
      _stateMachine->GetScene());
    return gameFinishedState;
  }

  return nullptr;
}

void GameplayState::OnEventTriggered(const IEvent& event)
{
  if (event.GetName() != EventNames::ALL_BRICKS_DESTROYED)
  {
    return;
  }

  _isComplete = true;
}

GameFinishedState::GameFinishedState(
  GameStateMachinePtr stateMachine,
  ScenePtr scene) :
    _stateMachine(stateMachine),
    _scene(scene)
{
}

void GameFinishedState::OnEnter()
{
  auto ball = _scene->FindGameEntityOfType(typeid(Ball));
  _scene->RemoveGameEntity(ball);

  auto paddle = _scene->FindGameEntityOfType(typeid(Paddle));
  _scene->RemoveGameEntity(paddle);

  auto timeTracker = std::static_pointer_cast<TimeTracker>(
    _scene->FindGameEntityOfType(typeid(TimeTracker)));
  timeTracker->PauseTimer();

  //TODO: Load this from data instead of hard-coding it
  Application::GetInstance()->LoadScene("Assets/Scenes/CompletionScreen.json");
}

void GameFinishedState::OnExit()
{
}

std::unique_ptr<IGameState> GameFinishedState::Update(float dt)
{
  return nullptr;
}