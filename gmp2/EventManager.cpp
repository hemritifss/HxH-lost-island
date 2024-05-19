#include "EventManager.hpp"
#include <iostream>

namespace HxH {

    // Check if a sprite is clicked with the mouse button or if the Escape key is pressed
    bool EventManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window) {
        if (sf::Mouse::isButtonPressed(button)) {
            sf::IntRect boundingBox(
                static_cast<int>(object.getPosition().x),
                static_cast<int>(object.getPosition().y),
                static_cast<int>(object.getGlobalBounds().width),
                static_cast<int>(object.getGlobalBounds().height)
            );

            if (boundingBox.contains(sf::Mouse::getPosition(window))) {
                return true;
            }
        }

        // Check if the Escape key is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            std::cout << "Espace key pressed" << std::endl;
            return true;
        }

        return false;
    }

    // Get the current mouse position relative to the window
    sf::Vector2i EventManager::GetMousePos(sf::RenderWindow& window) {
        return sf::Mouse::getPosition(window);
    }
}
