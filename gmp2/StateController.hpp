#pragma once

#include <stack>
#include <memory>
#include "Stage.hpp"

namespace HxH {
    using StageRef = std::unique_ptr<Stage>;

    class StateController {
    public:
        void AddState(StageRef newState, bool isReplacing = true);
        void RemoveState();
        void ProcessStateChanges();
        StageRef& GetActiveState();

    private:
        std::stack<StageRef> _states;
        StageRef _newState;
        
        bool _isAdding = false;
        bool _isReplacing = true;
        bool _isRemoving = false;
    };
}
