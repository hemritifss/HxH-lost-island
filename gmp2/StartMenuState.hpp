#pragma once

#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include "Stage.hpp"
#include "Engine.hpp"

namespace HxH {
    class StartMenuState : public Stage {
    public:
        StartMenuState(EngineDataRef data);

        void Init() override;
        void ProcessInput() override;
        void Update(float dt) override;
        void Render(float dt) override;

    private:
        EngineDataRef _refData;
		sf::Sound _startingSound;
		sf::SoundBuffer _startingSoundBuffer;
        sf::Sprite _bgSprite;
        sf::Sprite _titleSprite;
        sf::Sprite _startBtnSprite;
    };
}
