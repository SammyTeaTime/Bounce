#include "GameEntities/GameStateMachine.h"

#include "GameStates/GameStates.h"

void GameStateMachine::Setup() {}

void GameStateMachine::Start() 
{
  auto basePtr = shared_from_this();
  auto derivedPtr = std::static_pointer_cast<GameStateMachine>(basePtr);

  _state = std::make_unique<GameplayState>(derivedPtr, _eventService);
  _state->OnEnter();
}

void GameStateMachine::Update(float dt) 
{
  if (_state == nullptr)
  {
    return;
  }

  auto newState = _state->Update(dt);
  if (newState != nullptr)
  {
    _state->OnExit();
    newState->OnEnter();
    _state = std::move(newState);
  }
}

void GameStateMachine::Render(sf::RenderWindow& window) {}

void GameStateMachine::Destroy() {}