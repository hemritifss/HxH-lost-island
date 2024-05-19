#pragma once

#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <vector>
#include "Stage.hpp"
#include "Engine.hpp"
#include "Obstacles.hpp"
#include "Ground.hpp"
#include "Player.hpp"
#include "Blink.hpp"
#include "ScoreDisplay.hpp"
#include "Enemy.hpp"
#include "Collider.hpp"

namespace HxH {
    class PlayState : public Stage {
    public:
        PlayState(EngineDataRef data);

        void Init() override;
        void ProcessInput() override;
        void Update(float dt) override;
        void Render(float dt) override;

    private:
        EngineDataRef _refData;

        sf::Sprite _bgSprite;
        int _score;
        GameStates _currentState;
        sf::Clock clock;

        sf::SoundBuffer _startingSoundBuffer,_collisionSoundBuffer, _flapSoundBuffer, _pointSoundBuffer;
        sf::Sound _startingSound,_collisionSound, _flapSound, _pointSound;

        std::unique_ptr<Obstacles> obstacles;
        std::unique_ptr<Ground> ground;
        std::unique_ptr<Player> player;
        std::unique_ptr<Blink> blink;
        std::unique_ptr<ScoreDisplay> scoreDisplay;
        std::unique_ptr<Enemy> enemy;

        Collider collider;
    };
}
