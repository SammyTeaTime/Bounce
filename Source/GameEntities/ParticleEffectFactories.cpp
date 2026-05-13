#include "GameEntities/ParticleEffectFactories.h"

#include <plog/Log.h>

#include "GameEntities/BurstParticleEffect.h"

IGameEntityPtr BurstParticleEffectFactory::Create(const Json& data)
{
  float lifetime = data["lifetime"];
  unsigned int numParticlesPerBurst = data["numParticlesPerBurst"];
  sf::Vector2f particleSize =
  {
    data["particleSize"]["x"],
    data["particleSize"]["y"]
  };
  sf::Color particleColour = sf::Color(
    data["particleColour"]["r"],
    data["particleColour"]["g"],
    data["particleColour"]["b"],
    data["particleColour"]["a"]);
  float speedMin = data["speedMin"];
  float speedMax = data["speedMax"];
  sf::Vector2f gravity =
  {
    data["gravity"]["x"],
    data["gravity"]["y"]
  };
  auto effect = std::make_shared<BurstParticleEffect>(lifetime,
    numParticlesPerBurst, particleSize, particleColour, speedMin,
    speedMax, gravity);

  return effect;
}