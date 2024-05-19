#include "Blink.hpp"

namespace HxH {
    Blink::Blink(EngineDataRef data) : _refData(data), _isBlinking(true) {
        _rectShape = sf::RectangleShape(sf::Vector2f(_refData->wnd.getSize()));
        _rectShape.setFillColor(sf::Color(255, 255, 255, 0));
    }

    void Blink::Toggle(float dt) {
        if (_isBlinking) {
            int alpha = static_cast<int>(_rectShape.getFillColor().a + (BLINK_SPEED * dt));
            if (alpha >= 255) {
                alpha = 255;
                _isBlinking = false;
            }
            _rectShape.setFillColor(sf::Color(255, 255, 255, alpha));
        } else {
            int alpha = static_cast<int>(_rectShape.getFillColor().a - (BLINK_SPEED * dt));
            if (alpha <= 0) {
                alpha = 0;
            }
            _rectShape.setFillColor(sf::Color(255, 255, 255, alpha));
        }
    }

    void Blink::Render() {
        _refData->wnd.draw(_rectShape);
    }
}
