#pragma once

#include <SFML/Graphics.hpp>

namespace HxH {
    class EventManager {
    public:
        bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);
        sf::Vector2i GetMousePos(sf::RenderWindow& window);
    };
}
