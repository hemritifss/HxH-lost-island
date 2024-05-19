#include "Enemy.hpp"
#include "CONSTS.hpp"
#include <iostream>

namespace HxH {

    // Constructor to initialize the enemy with engine data
    Enemy::Enemy(EngineDataRef data) : _refData(data), _enemySpawnYOffset(0), _bulletRotation(0) {}

    // Spawn an enemy at a random vertical position
    void Enemy::SpawnEnemy() {
        sf::Sprite sprite(_refData->resManager.GetTexture("Enemy"));
        sprite.setPosition(
            _refData->wnd.getSize().x,
            rand() % static_cast<int>(_refData->wnd.getSize().y - sprite.getGlobalBounds().height)
        );
        _enemySprites.push_back(sprite);
    }

    // Move all enemies leftward and remove off-screen enemies
    void Enemy::MoveEnemy(float dt) {
        for (auto& sprite : _enemySprites) {
            sprite.move(-OBSTACLE_SPEED * dt, (float)-vibration);
			vibration*=-1;
        }

        _enemySprites.erase(
            std::remove_if(_enemySprites.begin(), _enemySprites.end(),
                [&](sf::Sprite& s) { return s.getPosition().x < -s.getGlobalBounds().width; }),
            _enemySprites.end());
    }

    // Render all enemy sprites
    void Enemy::RenderEnemy() {
        for (const auto& sprite : _enemySprites) {
            _refData->wnd.draw(sprite);
        }
    }

    // Shoot bullets from all enemies at regular intervals
    void Enemy::Shoot() {
        if (_shootClock.getElapsedTime().asSeconds() > SHOOT_INTERVAL) {
            for (const auto& enemy : _enemySprites) {
                sf::Sprite bullet(_refData->resManager.GetTexture("Bullet"));
                bullet.setOrigin(bullet.getGlobalBounds().width / 2, bullet.getGlobalBounds().height / 2);
                bullet.setPosition(enemy.getPosition().x, enemy.getPosition().y + enemy.getGlobalBounds().height / 2);
                _bullets.push_back(bullet);
            }
            _shootClock.restart();
        }
    }

    // Update the position and rotation of bullets, and remove off-screen bullets
    void Enemy::UpdateBullets(float dt) {
        for (auto& bullet : _bullets) {
            bullet.move(-BULLET_SPEED * dt, 0);
            _bulletRotation += ROTATION_SPEED * dt;
            if (_bulletRotation > 359.0f) {
                _bulletRotation = 0.f;
            }
            bullet.setRotation(_bulletRotation);
        }

        _bullets.erase(
            std::remove_if(_bullets.begin(), _bullets.end(),
                [&](sf::Sprite& b) { return b.getPosition().x < -b.getGlobalBounds().width; }),
            _bullets.end());
    }

    // Render all bullet sprites
    void Enemy::RenderBullets() {
        for (const auto& bullet : _bullets) {
            _refData->wnd.draw(bullet);
        }
    }

    // Get all enemy sprites (const version)
    const std::vector<sf::Sprite>& Enemy::GetSprites() const {
        return _enemySprites;
    }

    // Get all enemy sprites (non-const version)
    std::vector<sf::Sprite>& Enemy::GetSprites() {
        return _enemySprites;
    }

    // Get all bullet sprites
    const std::vector<sf::Sprite>& Enemy::GetBullets() const {
        return _bullets;
    }
}
