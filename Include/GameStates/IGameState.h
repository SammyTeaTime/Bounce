#pragma once

class IGameState
{
public:
  virtual ~IGameState() = default;
  virtual void OnEnter() = 0;
  virtual void OnExit() = 0;
  virtual std::unique_ptr<IGameState> Update(float dt) = 0;
};