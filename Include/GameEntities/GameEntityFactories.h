#pragma once

#include <TeaTimeEngine/Entities/IGameEntityFactory.h>

class BallFactory : public IGameEntityFactory
{
public:
  IGameEntityPtr Create(const Json& data) override;
};

class BrickFactory : public IGameEntityFactory
{
public:
  IGameEntityPtr Create(const Json& data) override;
};

class PaddleFactory : public IGameEntityFactory
{
public:
  IGameEntityPtr Create(const Json& data) override;
};

class ScoreBoardFactory : public IGameEntityFactory
{
public:
  IGameEntityPtr Create(const Json& data) override;
};