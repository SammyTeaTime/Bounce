#pragma once

#include <TeaTimeEngine/Entities/IParticleEffectFactory.h>

class BurstParticleEffectFactory : public IParticleEffectFactory
{
  IGameEntityPtr Create(const Json& data) override;
};