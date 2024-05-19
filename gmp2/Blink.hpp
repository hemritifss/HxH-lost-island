#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include "Engine.hpp"
#include "CONSTS.hpp"

namespace HxH {
    class Blink {
    public:
        Blink(EngineDataRef data);
        void Toggle(float dt);
        void Render();
    
    private:
        EngineDataRef _refData;
        sf::RectangleShape _rectShape;
        bool _isBlinking;
    };
}
