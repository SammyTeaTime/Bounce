#pragma once

#include <TeaTimeEngine/Entities/IGameEntityFactory.h>

class BurstParticleEffectFactory : public IGameEntityFactory
{
  IGameEntityPtr Create(const Json& data) override;
};