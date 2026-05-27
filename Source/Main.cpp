#include <TeaTimeEngine/Application.h>
#include <TeaTimeEngine/Services/IParticlesService.h>
#include <TeaTimeEngine/Services/IRandomService.h>
#include <TeaTimeEngine/Services/ISceneLoaderService.h>
#include <TeaTimeEngine/Services/ServiceLocator.h>

#include "GameEntities/GameEntityFactories.h"
#include "GameEntities/ParticleEffectFactories.h"

int main()
{
  Application application = Application();

  application.Setup();

  auto sceneLoaderService = ServiceLocator::GetService<ISceneLoaderService>();

  sceneLoaderService->RegisterFactory("Ball",
    std::make_shared<BallFactory>());
  sceneLoaderService->RegisterFactory("Brick",
    std::make_shared<BrickFactory>());
  sceneLoaderService->RegisterFactory("BricksMonitor",
    std::make_shared<BricksMonitorFactory>());
  sceneLoaderService->RegisterFactory("GameStateMachine",
    std::make_shared<GameStateMachineFactory>());
  sceneLoaderService->RegisterFactory("NumberDisplay",
    std::make_shared<NumberDisplayFactory>());
  sceneLoaderService->RegisterFactory("Paddle",
    std::make_shared<PaddleFactory>());
  sceneLoaderService->RegisterFactory("TimeTracker",
    std::make_shared<TimeTrackerFactory>());

  auto particlesService = ServiceLocator::GetService<IParticlesService>();

  particlesService->RegisterFactory("BurstParticleEffect",
    std::make_shared<BurstParticleEffectFactory>());
  particlesService->LoadParticleEffects();

  auto randomService = ServiceLocator::GetService<IRandomService>();
  randomService->Initialise();

  application.LoadStartupScene();

  while (application.IsWindowOpen())
  {
    application.ProcessEvents();
    application.Update();
    application.Render();
  }

  application.Destroy();
}