#include "Ground.hpp"

namespace HxH {

    // Constructor to initialize the ground with engine data
    Ground::Ground(EngineDataRef data) : _refData(data) {
        sf::Sprite sprite1(_refData->resManager.GetTexture("Ground"));
        sf::Sprite sprite2(_refData->resManager.GetTexture("Ground"));

        sprite1.setPosition(0, _refData->wnd.getSize().y - sprite1.getGlobalBounds().height);
        sprite2.setPosition(sprite1.getGlobalBounds().width, _refData->wnd.getSize().y - sprite2.getGlobalBounds().height);

        _groundSprites.push_back(sprite1);
        _groundSprites.push_back(sprite2);
    }

    // Move the ground sprites to create a scrolling effect
    void Ground::MoveGround(float dt) {
        float movement = OBSTACLE_SPEED * dt;

        for (auto& sprite : _groundSprites) {
            sprite.move(-movement, 0.0f);

            // Reset the position of the sprite if it moves off screen
            if (sprite.getPosition().x < -sprite.getGlobalBounds().width) {
                sprite.setPosition(_refData->wnd.getSize().x, sprite.getPosition().y);
            }
        }
    }

    // Render the ground sprites
    void Ground::RenderGround() {
        for (const auto& sprite : _groundSprites) {
            _refData->wnd.draw(sprite);
        }
    }

    // Get the ground sprites
    const std::vector<sf::Sprite>& Ground::GetSprites() const {
        return _groundSprites;
    }
}
