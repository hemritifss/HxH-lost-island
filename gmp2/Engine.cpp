#include "Engine.hpp"
#include "IntroState.hpp"
#include <cstdlib>
#include <ctime>

namespace HxH {

    // Constructor to initialize the engine with window settings and the first game state
    Engine::Engine(int width, int height, std::string title) {
        srand(static_cast<unsigned>(time(nullptr)));

        _refData->wnd.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
        _refData->wnd.setFramerateLimit(60);
        _refData->stateCtrl.AddState(StageRef(new IntroState(_refData)));

        this->Run();
    }

    // Main game loop
    void Engine::Run() {
        float currentTime = _gameClock.getElapsedTime().asSeconds();
        float accumulator = 0.0f;

        while (_refData->wnd.isOpen()) {
            _refData->stateCtrl.ProcessStateChanges();

            float newTime = _gameClock.getElapsedTime().asSeconds();
            float frameTime = newTime - currentTime;

            // Cap the frame time to avoid spiral of death
            if (frameTime > 0.25f) {
                frameTime = 0.25f;
            }

            currentTime = newTime;
            accumulator += frameTime;

            while (accumulator >= frameRate) {
                _refData->stateCtrl.GetActiveState()->ProcessInput();
                _refData->stateCtrl.GetActiveState()->Update(frameRate);
                accumulator -= frameRate;
            }

            _refData->stateCtrl.GetActiveState()->Render(frameRate);
        }
    }
}
