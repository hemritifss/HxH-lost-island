#pragma once

#include <SFML/Graphics.hpp>
#include "Stage.hpp"
#include "Engine.hpp"

namespace HxH {
    class EndGameState : public Stage {
    public:
        EndGameState(EngineDataRef data, int score);

        void Init() override;
        void ProcessInput() override;
        void Update(float dt) override;
        void Render(float dt) override;

    private:
        EngineDataRef _refData;
        int _score;
        int _highScore;

        sf::Sprite _bgSprite;
        sf::Sprite _gameOverTitle;
        sf::Sprite _gameOverContainer;
        sf::Sprite _retryBtn;
        sf::Sprite _medalSprite;

        sf::Text _scoreTxt;
        sf::Text _highScoreTxt;
    };
}
