#include <sstream>
#include "IntroState.hpp"
#include "StartMenuState.hpp"
#include "CONSTS.hpp"
#include <iostream>

namespace HxH {

    // Constructor to initialize the IntroState with engine data
    IntroState::IntroState(EngineDataRef data) : _refData(data) {}

    // Initialize the intro state: load the background texture
    void IntroState::Init() {
        _refData->resManager.LoadTexture("Intro State Background", INTRO_SCENE_BG_PATH);
        _bgSprite.setTexture(this->_refData->resManager.GetTexture("Intro State Background"));
    }

    // Handle user input: close window
    void IntroState::ProcessInput() {
        sf::Event event;
        while (_refData->wnd.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _refData->wnd.close();
            }
        }
    }

    // Update the state: transition to start menu after a certain time
    void IntroState::Update(float dt) {
        if (_clock.getElapsedTime().asSeconds() > INTRO_STATE_SHOW_TIME) {
            _refData->stateCtrl.AddState(StageRef(new StartMenuState(_refData)), true);
        }
    }

    // Render the intro state
    void IntroState::Render(float dt) {
        _refData->wnd.clear();
        _refData->wnd.draw(_bgSprite);
        _refData->wnd.display();
    }
}
