#include <sstream>
#include "StartMenuState.hpp"
#include "PlayState.hpp"
#include "CONSTS.hpp"
#include <iostream>

namespace HxH {

    // Constructor to initialize reference to engine data
    StartMenuState::StartMenuState(EngineDataRef data) : _refData(data) {}

    // Initialize the start menu: load textures and set up sprites
    void StartMenuState::Init() {
				if(!_startingSoundBuffer.loadFromFile(STARTING_SOUND_PATH)) {
            std::cerr << "Error loading starting Sound Effect" << std::endl;
        }
		_startingSound.setBuffer(_startingSoundBuffer);
		_startingSound.play();
        _refData->resManager.LoadTexture("Main Menu Background", MAIN_MENU_BG_PATH);
        _refData->resManager.LoadTexture("Game Title", GAME_TITLE_PATH);
        _refData->resManager.LoadTexture("Start Button", START_BTN_PATH);

        _bgSprite.setTexture(_refData->resManager.GetTexture("Main Menu Background"));
        _titleSprite.setTexture(_refData->resManager.GetTexture("Game Title"));
        _startBtnSprite.setTexture(_refData->resManager.GetTexture("Start Button"));

        // Center the title and start button
        _titleSprite.setPosition(
            (WINDOW_WIDTH / 2) - (_titleSprite.getGlobalBounds().width / 2),
            100
        );
        _startBtnSprite.setPosition(
            (WINDOW_WIDTH / 2) - (_startBtnSprite.getGlobalBounds().width / 2),
            700 
        );
    }

    // Handle user input: close window or start game
    void StartMenuState::ProcessInput() {
        sf::Event event;

        while (_refData->wnd.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _refData->wnd.close();
            }
            if (_refData->evtManager.IsSpriteClicked(_startBtnSprite, sf::Mouse::Left, _refData->wnd)) {
                _refData->stateCtrl.AddState(StageRef(new PlayState(_refData)), true);
            }
        }
    }

    // Update method: currently not used but required by interface
    void StartMenuState::Update(float dt) {}

    // Render the start menu
    void StartMenuState::Render(float dt) {
        _refData->wnd.clear();
        _refData->wnd.draw(_bgSprite);
        _refData->wnd.draw(_titleSprite);
        _refData->wnd.draw(_startBtnSprite);
        _refData->wnd.display();
    }
}
