#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Engine.hpp"

namespace HxH {
    class Enemy {
    public:
        Enemy(EngineDataRef data);

        void SpawnEnemy();
        void MoveEnemy(float dt);
        void RenderEnemy();
        void Shoot();
        void UpdateBullets(float dt);
        void RenderBullets();
        const std::vector<sf::Sprite>& GetSprites() const;  // Keep const version for other usages
        std::vector<sf::Sprite>& GetSprites();  // Non-const version for modifications
        const std::vector<sf::Sprite>& GetBullets() const;

    private:
		int vibration=3;
        EngineDataRef _refData;
        std::vector<sf::Sprite> _enemySprites;
        std::vector<sf::Sprite> _bullets;
        float _bulletRotation;
        sf::Clock _shootClock;
        float _enemySpawnYOffset;  // Ensure this is declared as a member variable
    };
}
