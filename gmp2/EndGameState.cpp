#include <sstream>
#include <iostream>
#include <fstream>
#include "EndGameState.hpp"
#include "CONSTS.hpp"
#include "PlayState.hpp"

namespace HxH {

    // Constructor to initialize the end game state with engine data and score
    EndGameState::EndGameState(EngineDataRef data, int score) : _refData(data), _score(score) {}

    // Initialize the end game state: load resources, set up sprites and text
    void EndGameState::Init() {
        // Load high score from file
        std::ifstream readFile("resources/highscore.txt");
        if (readFile.is_open()) {
            readFile >> _highScore;
        }
        readFile.close();

        // Update high score if current score is higher
        if (_score > _highScore) {
            _highScore = _score;
            std::ofstream writeFile("resources/highscore.txt");
            if (writeFile.is_open()) {
                writeFile << _highScore;
            }
            writeFile.close();
        }

        // Load textures
        _refData->resManager.LoadTexture("Game Over Background", GAME_OVER_BG_PATH);
        _refData->resManager.LoadTexture("Game Over Title", GAME_OVER_TITLE_PATH);
        _refData->resManager.LoadTexture("Game Over Body", GAME_OVER_BODY_PATH);
        _refData->resManager.LoadTexture("Bronze Medal", BRONZE_MEDAL_PATH);
        _refData->resManager.LoadTexture("Silver Medal", SILVER_MEDAL_PATH);
        _refData->resManager.LoadTexture("Gold Medal", GOLD_MEDAL_PATH);
        _refData->resManager.LoadTexture("Platinum Medal", PLATINUM_MEDAL_PATH);
        _refData->resManager.LoadTexture("Start Button", START_BTN_PATH);

        // Set textures to sprites
        _bgSprite.setTexture(_refData->resManager.GetTexture("Game Over Background"));
        _gameOverTitle.setTexture(_refData->resManager.GetTexture("Game Over Title"));
        _gameOverContainer.setTexture(_refData->resManager.GetTexture("Game Over Body"));
        _retryBtn.setTexture(_refData->resManager.GetTexture("Start Button"));

        // Set positions of sprites
        _gameOverContainer.setPosition(
            (_refData->wnd.getSize().x / 2) - (_gameOverContainer.getGlobalBounds().width / 2),
            (_refData->wnd.getSize().y / 2) - (_gameOverContainer.getGlobalBounds().height / 2)
        );

        _gameOverTitle.setPosition(
            (_refData->wnd.getSize().x / 2) - (_gameOverTitle.getGlobalBounds().width / 2),
            _gameOverContainer.getPosition().y - (_gameOverTitle.getGlobalBounds().height * 1.2f)
        );

        _retryBtn.setPosition(
            (_refData->wnd.getSize().x / 2) - (_retryBtn.getGlobalBounds().width / 2),
            _gameOverContainer.getPosition().y + _gameOverContainer.getGlobalBounds().height + 
            _retryBtn.getGlobalBounds().height * 0.2f
        );

        // Set up score text
        _scoreTxt.setFont(_refData->resManager.GetFont("Flappy Font"));
        _scoreTxt.setString(std::to_string(_score));
        _scoreTxt.setCharacterSize(56);
        _scoreTxt.setFillColor(sf::Color::White);
        _scoreTxt.setOrigin(_scoreTxt.getGlobalBounds().width / 2, _scoreTxt.getGlobalBounds().height / 2);
        _scoreTxt.setPosition(_refData->wnd.getSize().x / 10 * 7.25f, _refData->wnd.getSize().y / 2.15f);

        // Set up high score text
        _highScoreTxt.setFont(_refData->resManager.GetFont("Flappy Font"));
        _highScoreTxt.setString(std::to_string(_highScore));
        _highScoreTxt.setCharacterSize(56);
        _highScoreTxt.setFillColor(sf::Color::White);
        _highScoreTxt.setOrigin(_highScoreTxt.getGlobalBounds().width / 2, _highScoreTxt.getGlobalBounds().height / 2);
        _highScoreTxt.setPosition(_refData->wnd.getSize().x / 10 * 7.25f, _refData->wnd.getSize().y / 1.78f);

        // Set up medal based on score
        if (_score >= PLATINUM_MEDAL_SCORE) {
            _medalSprite.setTexture(_refData->resManager.GetTexture("Platinum Medal"));
        } else if (_score >= GOLD_MEDAL_SCORE) {
            _medalSprite.setTexture(_refData->resManager.GetTexture("Gold Medal"));
        } else if (_score >= SILVER_MEDAL_SCORE) {
            _medalSprite.setTexture(_refData->resManager.GetTexture("Silver Medal"));
        } else if (_score >= BRONZE_MEDAL_SCORE) {
            _medalSprite.setTexture(_refData->resManager.GetTexture("Bronze Medal"));
        }
        _medalSprite.setPosition(175, 465);
    }

    // Handle user input: close window or retry game
    void EndGameState::ProcessInput() {
        sf::Event event;
        while (_refData->wnd.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _refData->wnd.close();
            }
            if (_refData->evtManager.IsSpriteClicked(_retryBtn, sf::Mouse::Left, _refData->wnd)) {
                _refData->stateCtrl.AddState(StageRef(new PlayState(_refData)), true);
            }
        }
    }

    // Update the state (not used in this state)
    void EndGameState::Update(float dt) {}

    // Render the end game state
    void EndGameState::Render(float dt) {
        _refData->wnd.clear();
        _refData->wnd.draw(_bgSprite);
        _refData->wnd.draw(_gameOverTitle);
        _refData->wnd.draw(_gameOverContainer);
        _refData->wnd.draw(_retryBtn);
        _refData->wnd.draw(_scoreTxt);
        _refData->wnd.draw(_highScoreTxt);
        _refData->wnd.draw(_medalSprite);
        _refData->wnd.display();
    }
}
