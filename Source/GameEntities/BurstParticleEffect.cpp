#include "GameEntities/BurstParticleEffect.h"

BurstParticleEffect::BurstParticleEffect(float lifetime,
  unsigned int numParticlesPerBurst, sf::Vector2f particleSize,
  sf::Color particleColour, float speedMin, float speedMax,
  sf::Vector2f gravity) :
  _lifetime(lifetime), _numParticlesPerBurst(numParticlesPerBurst),
  _particleSize(particleSize), _particleColour(particleColour),
  _speedMin(speedMin), _speedMax(speedMax), _gravity(gravity)
{
  for (unsigned int i = 0; i < _particles.size(); ++i)
  {
    _particles[i].setSize(particleSize);
    _particles[i].setOrigin(particleSize * 0.5f);
    _particles[i].setFillColor(_particleColour);
    _particleActive[i] = false;
  }
}

void BurstParticleEffect::Play()
{
  _isPlaying = true;
  _activeTime = 0.0f;

  for (unsigned int i = 0; i < _numParticlesPerBurst; i++)
  {
    sf::RectangleShape& particle = _particles[_particleIterator];
    particle.setPosition(_position);

    _particleActive[_particleIterator] = true;
    _particleVelocities[_particleIterator] = sf::Vector2f(_speedMin +
      static_cast<float>(rand()) / (static_cast<float>(RAND_MAX /
        (_speedMax - _speedMin))), 0.0f).rotatedBy(
          sf::degrees(static_cast<float>(rand()) /
            (static_cast<float>(RAND_MAX / 360.0f))));

    _particleIterator += 1;
    if (_particleIterator >= _particles.size())
    {
      _particleIterator = 0;
    }
  }
}

void BurstParticleEffect::Stop()
{
  _isPlaying = false;

  for (unsigned int i = 0; i < _particles.size(); ++i)
  {
    _particleActive[i] = false;
  }
}

void BurstParticleEffect::SetColour(const sf::Color& colour)
{
  _particleColour = colour;
  for (unsigned int i = 0; i < _particles.size(); ++i)
  {
    _particles[i].setFillColor(_particleColour);
  }
}

void BurstParticleEffect::Setup()
{
}

void BurstParticleEffect::Start()
{
}

void BurstParticleEffect::Update(const float dt)
{
  if (!_isPlaying)
  {
    return;
  }

  for (unsigned int i = 0; i < _particles.size(); ++i)
  {
    if (!_particleActive[i])
    {
      continue;
    }

    _particles[i].move(_particleVelocities[i] * dt);
    _particleVelocities[i] += _gravity * dt;
  }

  _activeTime += dt;
  if (_activeTime >= _lifetime)
  {
    Stop();
  }
}

void BurstParticleEffect::Render(sf::RenderWindow& window)
{
  if (!_isPlaying)
  {
    return;
  }

  for (unsigned int i = 0; i < _particles.size(); ++i)
  {
    if (!_particleActive[i])
    {
      continue;
    }

    window.draw(_particles[i]);
  }
}

void BurstParticleEffect::Destroy()
{
}