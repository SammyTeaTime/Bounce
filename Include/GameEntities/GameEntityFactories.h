#pragma once

#include <TeaTimeEngine/Entities/IGameEntityFactory.h>

class BallFactory : public IGameEntityFactory
{
public:
  IGameEntityPtr Create(const Json& data, ScenePtr scene) override;
};

class BrickFactory : public IGameEntityFactory
{
public:
  IGameEntityPtr Create(const Json& data, ScenePtr scene) override;
};

class BricksMonitorFactory : public IGameEntityFactory
{
public:
  IGameEntityPtr Create(const Json& data, ScenePtr scene) override;
};

class GameStateMachineFactory : public IGameEntityFactory
{
public:
  IGameEntityPtr Create(const Json& data, ScenePtr scene) override;
};

class PaddleFactory : public IGameEntityFactory
{
public:
  IGameEntityPtr Create(const Json& data, ScenePtr scene) override;
};

class NumberDisplayFactory : public IGameEntityFactory
{
public:
  IGameEntityPtr Create(const Json& data, ScenePtr scene) override;
};

class TimeTrackerFactory : public IGameEntityFactory
{
public:
  IGameEntityPtr Create(const Json& data, ScenePtr scene) override;
};