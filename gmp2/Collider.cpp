#include "Collider.hpp"

namespace HxH {

    // Constructor
    Collider::Collider() {}

    // Check for collision between two sprites
    bool Collider::CheckSpriteCollision(sf::Sprite sprite1, sf::Sprite sprite2) {
        sf::FloatRect rect1 = sprite1.getGlobalBounds();
        sf::FloatRect rect2 = sprite2.getGlobalBounds();

        return rect1.intersects(rect2);
    }

    // Check for collision between two sprites with scaling
    bool Collider::CheckSpriteCollision(sf::Sprite sprite1, float scale1, sf::Sprite sprite2, float scale2) {
        sprite1.setScale(scale1, scale1);
        sprite2.setScale(scale2, scale2);

        sf::FloatRect rect1 = sprite1.getGlobalBounds();
        sf::FloatRect rect2 = sprite2.getGlobalBounds();

        return rect1.intersects(rect2);
    }
}
