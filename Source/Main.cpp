#include <TeaTimeEngine/Application.h>
#include <TeaTimeEngine/Services/IParticleEffectService.h>
#include <TeaTimeEngine/Services/ISceneLoaderService.h>
#include <TeaTimeEngine/Services/ServiceLocator.h>

#include "GameEntities/GameEntityFactories.h"
#include "GameEntities/ParticleEffectFactories.h"

int main()
{
  Application application = Application();

  application.Setup();

  auto sceneLoaderService = ServiceLocator::GetInstance()->
    GetService<ISceneLoaderService>();

  sceneLoaderService->RegisterGameEntityFactory("Ball", 
    std::make_shared<BallFactory>());
  sceneLoaderService->RegisterGameEntityFactory("Brick",
    std::make_shared<BrickFactory>());
  sceneLoaderService->RegisterGameEntityFactory("Paddle",
    std::make_shared<PaddleFactory>());

  auto particleEffectService = ServiceLocator::GetInstance()->
    GetService<IParticleEffectService>();

  particleEffectService->RegisterGameEntityFactory("BurstParticleEffect", 
    std::make_shared<BurstParticleEffectFactory>());
  particleEffectService->LoadParticleEffects();

  application.LoadStartupScene();

  while (application.IsWindowOpen())
  {
    application.ProcessEvents();
    application.Update();
    application.Render();
  }

  application.Destroy();
}