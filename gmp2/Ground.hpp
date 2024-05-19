#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Engine.hpp"
#include "CONSTS.hpp"

namespace HxH {
    class Ground {
    public:
        Ground(EngineDataRef data);

        void MoveGround(float dt);
        void RenderGround();
        const std::vector<sf::Sprite>& GetSprites() const;

    private:
        EngineDataRef _refData;
        std::vector<sf::Sprite> _groundSprites;
    };
}
