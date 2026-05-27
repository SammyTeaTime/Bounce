#include "GameEntities/BricksMonitor.h"

#include <TeaTimeEngine/Events/GenericEvent.h>
#include <TeaTimeEngine/Scene.h>
#include <TeaTimeEngine/Services/IEventService.h>

//Begin Debug only
#include <TeaTimeEngine/Application.h>
#include <TeaTimeEngine/Services/IRandomService.h>
#include <TeaTimeEngine/Services/ServiceLocator.h>
//End Debug only

#include "Events/EntityListUpdatedEvent.h"
#include "Events/EventNames.h"
#include "Events/GameEntityDestroyedEvent.h"
#include "GameEntities/Brick.h"

void BricksMonitor::Setup() 
{
  _eventService->RegisterListener(EventNames::BRICK_DESTROYED, this);
}

void BricksMonitor::Start()
{
  auto foundEntities = _scene->FindGameEntitiesOfType(typeid(Brick));

  _bricks = std::make_shared<EntityList>(foundEntities);

  SendBricksUpdatedEvent();
}

//Begin Debug only
bool canPressB = true;
//End Debug only

void BricksMonitor::Update(float dt)
{
//Begin Debug only
  if (_bricks->size() == 0)
  {
    return;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B) && canPressB)
  {
    canPressB = false;

    auto randomService = ServiceLocator::GetService<IRandomService>();
    auto randomBrickIndex = randomService->RandomInRange(0, _bricks->size());
    auto& randomBrick = (*_bricks)[randomBrickIndex];

    auto& scenes = Application::GetInstance()->GetScenes();
    for (auto& scene : scenes)
    {
      scene->RemoveGameEntity(randomBrick);
    }
  }
  
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B) == false)
  {
    canPressB = true;
  }
//End Debug only
}

void BricksMonitor::Render(sf::RenderWindow& window) {}

void BricksMonitor::Destroy()
{
  _eventService->UnregisterListener(EventNames::BRICK_DESTROYED, this);
}

void BricksMonitor::OnEventTriggered(const IEvent& event)
{
  if (event.GetName() == EventNames::BRICK_DESTROYED)
  {
    auto& gameEntityDestroyedEvent =
      static_cast<const GameEntityDestroyedEvent&>(event);
    auto gameEntity = gameEntityDestroyedEvent.GetGameEntity();
    auto brick = static_pointer_cast<Brick>(gameEntity);

    _bricks->erase(std::remove(_bricks->begin(), _bricks->end(), gameEntity));

    SendBricksUpdatedEvent();

    if (_bricks->size() == 0)
    {
      auto allBricksDestroyedEvent = GenericEvent(
        EventNames::ALL_BRICKS_DESTROYED);
      _eventService->ReceiveEvent(allBricksDestroyedEvent);
    }
  }
  else if (event.GetName() == EventNames::REQUEST_BRICKS_UPDATE)
  {
    SendBricksUpdatedEvent();
  }
}

void BricksMonitor::SendBricksUpdatedEvent() const
{
  auto bricksUpdatedEvent = EntityListUpdatedEvent(
    EventNames::BRICKS_UPDATED,
    _bricks);
  _eventService->ReceiveEvent(bricksUpdatedEvent);
}