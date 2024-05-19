#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include "Engine.hpp"
#include "CONSTS.hpp"

namespace HxH {
    class Obstacles {
    public:
        Obstacles(EngineDataRef data);

        void SpawnBottomObstacle();
        void SpawnTopObstacle();
        void SpawnInvisibleObstacle();
        void SpawnScoringObstacle();
        void MoveObstacles(float dt);
        void RenderObstacles();
        void RandomizeObstacleOffset();

        const std::vector<sf::Sprite>& GetSprites() const;
        std::vector<sf::Sprite>& GetScoringSprites();

    private:
        EngineDataRef _refData;
        std::vector<sf::Sprite> obstacleSprites;
        std::vector<sf::Sprite> scoringObstacles;

        int _groundHeight;
        int _obstacleSpawnYOffset;
    };
}
