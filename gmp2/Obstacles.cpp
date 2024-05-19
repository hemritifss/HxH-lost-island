#include "Obstacles.hpp"
#include <iostream>

namespace HxH {

    // Constructor to initialize the obstacles with engine data
    Obstacles::Obstacles(EngineDataRef data) : _refData(data) {
        _groundHeight = _refData->resManager.GetTexture("Ground").getSize().y;
        _obstacleSpawnYOffset = 0;
    }

    // Spawn a bottom obstacle
    void Obstacles::SpawnBottomObstacle() {
        sf::Sprite sprite(_refData->resManager.GetTexture("Obstacle Up"));
        sprite.setPosition(
            _refData->wnd.getSize().x,
            _refData->wnd.getSize().y - sprite.getGlobalBounds().height - _obstacleSpawnYOffset
        );
        obstacleSprites.push_back(sprite);
    }

    // Spawn a top obstacle
    void Obstacles::SpawnTopObstacle() {
        sf::Sprite sprite(_refData->resManager.GetTexture("Obstacle Down"));
        sprite.setPosition(_refData->wnd.getSize().x, -_obstacleSpawnYOffset);
        obstacleSprites.push_back(sprite);
    }

    // Spawn an invisible obstacle
    void Obstacles::SpawnInvisibleObstacle() {
        sf::Sprite sprite(_refData->resManager.GetTexture("Obstacle Up"));
        sprite.setPosition(
            _refData->wnd.getSize().x,
            _refData->wnd.getSize().y - sprite.getGlobalBounds().height
        );
        sprite.setColor(sf::Color(0, 0, 0, 0));
        obstacleSprites.push_back(sprite);
    }

    // Spawn a scoring obstacle
    void Obstacles::SpawnScoringObstacle() {
        sf::Sprite sprite(_refData->resManager.GetTexture("Scoring Obstacle"));
        sprite.setPosition(_refData->wnd.getSize().x, 0);
        scoringObstacles.push_back(sprite);
    }

    // Move obstacles across the screen
    void Obstacles::MoveObstacles(float dt) {
        // Move obstacle sprites
        for (size_t i = 0; i < obstacleSprites.size(); ++i) {
            if (obstacleSprites[i].getPosition().x < 0 - obstacleSprites[i].getGlobalBounds().width) {
                obstacleSprites.erase(obstacleSprites.begin() + i);
            } else {
                float movement = OBSTACLE_SPEED * dt;
                obstacleSprites[i].move(-movement, 0);
            }
        }

        // Move scoring obstacles
        for (size_t i = 0; i < scoringObstacles.size(); ++i) {
            if (scoringObstacles[i].getPosition().x < 0 - scoringObstacles[i].getGlobalBounds().width) {
                scoringObstacles.erase(scoringObstacles.begin() + i);
            } else {
                float movement = OBSTACLE_SPEED * dt;
                scoringObstacles[i].move(-movement, 0);
            }
        }
    }

    // Render all obstacles
    void Obstacles::RenderObstacles() {
        for (const auto& sprite : obstacleSprites) {
            _refData->wnd.draw(sprite);
        }
    }

    // Randomize the vertical offset for obstacle spawning
    void Obstacles::RandomizeObstacleOffset() {
        _obstacleSpawnYOffset = rand() % (_groundHeight + 1); 
    }

    // Get the obstacle sprites
    const std::vector<sf::Sprite>& Obstacles::GetSprites() const {
        return obstacleSprites;
    }

    // Get the scoring obstacle sprites
    std::vector<sf::Sprite>& Obstacles::GetScoringSprites() {
        return scoringObstacles;
    }
    // Get the scoring obstacle sprites (non-const version)
    
}
