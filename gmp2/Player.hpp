#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Engine.hpp"
#include "CONSTS.hpp"

namespace HxH {
    class Player {
    public:
        Player(EngineDataRef data);

        void Render();
        void Animate(float dt);
        void Update(float dt);
        void Jump();
        bool isJumping() const;
        const sf::Sprite& GetSprite() const;

    private:
        EngineDataRef _refData;
        sf::Sprite _playerSprite;
        std::vector<sf::Texture> _animationFrames;
        unsigned int _animIterator;
        sf::Clock _clock, _movementClock;

        int _playerState;
        float _rotation;
    };
}
