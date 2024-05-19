#pragma once

#include <SFML/Graphics.hpp>
#include "Engine.hpp"

namespace HxH {
    class ScoreDisplay {
    public:
        ScoreDisplay(EngineDataRef data);

        void Render();
        void UpdateScore(int score);

    private:
        EngineDataRef _refData;
        sf::Text _scoreTxt;
    };
}
