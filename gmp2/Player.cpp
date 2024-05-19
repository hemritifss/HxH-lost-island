#include "Player.hpp"

namespace HxH {

    // Constructor to initialize the player with engine data
    Player::Player(EngineDataRef data) : _refData(data), _animIterator(0), _playerState(PLAYER_STATE_STILL), _rotation(0) {
        _animationFrames.push_back(_refData->resManager.GetTexture("Player Frame 1"));
        _animationFrames.push_back(_refData->resManager.GetTexture("Player Frame 2"));
        _animationFrames.push_back(_refData->resManager.GetTexture("Player Frame 3"));
        _animationFrames.push_back(_refData->resManager.GetTexture("Player Frame 4"));

        _playerSprite.setTexture(_animationFrames.at(_animIterator));

        // Set the initial position of the player sprite
        _playerSprite.setPosition(
            (_refData->wnd.getSize().x / 4) - (_playerSprite.getGlobalBounds().width / 2),
            (_refData->wnd.getSize().y / 2) - (_playerSprite.getGlobalBounds().height / 2)
        );

        // Set the origin of the sprite to its center for rotation
        sf::Vector2f origin = sf::Vector2f(
            _playerSprite.getGlobalBounds().width / 2,
            _playerSprite.getGlobalBounds().height / 2
        );
        _playerSprite.setOrigin(origin);
    }

    // Render the player sprite on the window
    void Player::Render() {
        _refData->wnd.draw(_playerSprite);
    }

    // Animate the player by cycling through the animation frames
    void Player::Animate(float dt) {
        if (_clock.getElapsedTime().asSeconds() > PLAYER_ANIMATION_DURATION / _animationFrames.size()) {
            _animIterator = (_animIterator + 1) % _animationFrames.size();
            _playerSprite.setTexture(_animationFrames.at(_animIterator));
            _clock.restart();
        }
    }

    // Update the player's position and state
    void Player::Update(float dt) {
        if (_playerState == PLAYER_STATE_FALLING) {
            _playerSprite.move(0, GRAVITY * dt);
            _rotation += ROTATION_SPEED * dt;
            if (_rotation > 25.0f) _rotation = 25.0f;
        } else if (_playerState == PLAYER_STATE_FLYING) {
            _playerSprite.move(0, -FLYING_SPEED * dt);
            _rotation -= ROTATION_SPEED * dt;
            if (_rotation < -25.0f) _rotation = -25.0f;
        }
        _playerSprite.setRotation(_rotation);

        // Reset the player state to falling after flying duration
        if (_movementClock.getElapsedTime().asSeconds() > FLYING_DURATION) {
            _movementClock.restart();
            _playerState = PLAYER_STATE_FALLING;
        }
    }
    // Make the player jump
    void Player::Jump() {
        _movementClock.restart();
        _playerState = PLAYER_STATE_FLYING;
    }
    //Get if the player is jumping or not
    bool Player::isJumping() const {
        return _playerState == PLAYER_STATE_FLYING;
    }
    // Get the player's sprite
    const sf::Sprite& Player::GetSprite() const {
        return _playerSprite;
    }
}
