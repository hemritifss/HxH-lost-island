#pragma once

#include <SFML/Graphics.hpp>
#include "StateController.hpp"
#include "ResourceManager.hpp"
#include "EventManager.hpp"

namespace HxH {
    struct EngineData {
        sf::RenderWindow wnd;
        ResourceManager resManager;
        StateController stateCtrl;
        EventManager evtManager;
    };

    typedef std::shared_ptr<EngineData> EngineDataRef;

    class Engine {
    public:
        Engine(int width, int height, std::string title);
        void Run();

    private:
        const float frameRate = 1.0f / 60.0f;
        sf::Clock _gameClock;
        EngineDataRef _refData = std::make_shared<EngineData>();
    };
}
