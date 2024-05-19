#pragma once

#include <SFML/Graphics.hpp>
#include "Stage.hpp"
#include "Engine.hpp"

namespace HxH {
    class IntroState : public Stage {
    public:
        IntroState(EngineDataRef data);

        void Init() override;
        void ProcessInput() override;
        void Update(float dt) override;
        void Render(float dt) override;

    private:
        EngineDataRef _refData;
        sf::Sprite _bgSprite;
        sf::Clock _clock;
    };
}
