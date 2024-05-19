#include "ScoreDisplay.hpp"
#include <string>

namespace HxH {

    // Constructor to initialize score display
    ScoreDisplay::ScoreDisplay(EngineDataRef data) : _refData(data) {
        _scoreTxt.setFont(_refData->resManager.GetFont("Flappy Font"));
        _scoreTxt.setString("0");
        _scoreTxt.setCharacterSize(128);
        _scoreTxt.setFillColor(sf::Color::White);

        // Center the text origin
        _scoreTxt.setOrigin(
            _scoreTxt.getGlobalBounds().width / 2,
            _scoreTxt.getGlobalBounds().height / 2
        );

        // Position the text on the screen
        _scoreTxt.setPosition(
            _refData->wnd.getSize().x / 2,
            _refData->wnd.getSize().y / 5
        );
    }

    // Render the score display on the window
    void ScoreDisplay::Render() {
        _refData->wnd.draw(_scoreTxt);
    }

    // Update the score displayed
    void ScoreDisplay::UpdateScore(int score) {
        _scoreTxt.setString(std::to_string(score));
    }
}
