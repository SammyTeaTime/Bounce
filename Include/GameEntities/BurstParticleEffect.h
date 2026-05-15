#pragma once

#include <array>

#include <SFML/Graphics.hpp>
#include <TeaTimeEngine/Entities/IParticleEffect.h>

class BurstParticleEffect : public IParticleEffect
{
  IGAMEENTITY_DECLARATION();

private:
  std::array<sf::RectangleShape, 128> _particles;
  std::array<sf::Vector2f, 128> _particleVelocities;
  std::array<bool, 128> _particleActive;
  unsigned int _particleIterator = 0;
  sf::Vector2f _position;
  bool _isPlaying = false;
  float _activeTime = 0.0f;

  float _lifetime;
  unsigned int _numParticlesPerBurst;
  sf::Vector2f _particleSize;
  sf::Color _particleColour;
  float _speedMin;
  float _speedMax;
  sf::Vector2f _gravity;

public:
  BurstParticleEffect(float lifetime, unsigned int numParticlesPerBurst,
    sf::Vector2f particleSize, sf::Color particleColour, float speedMin,
    float speedMax, sf::Vector2f gravity);
  ~BurstParticleEffect() = default;

  IParticleEffectPtr Clone() override
  {
    return std::make_shared<BurstParticleEffect>(_lifetime,
      _numParticlesPerBurst, _particleSize, _particleColour, _speedMin,
      _speedMax, _gravity);
  }

  void Play() override;
  void Stop() override;

  void Setup() override;
  void Start() override;
  void Update(const float dt) override;
  void Render(sf::RenderWindow& window) override;
  void Destroy() override;

  sf::Vector2f GetPosition() const override { return _position; }
  void SetPosition(const sf::Vector2f& position) override
  {
    _position = position;
  }

  sf::Color GetColour() const override { return _particleColour; }
  void SetColour(const sf::Color& colour) override;
};