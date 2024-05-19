#include "StateController.hpp"

namespace HxH {

    // Adds a new state, specifying whether it should replace the current state
    void StateController::AddState(StageRef newState, bool isReplacing) {
        this->_isAdding = true;
        this->_isReplacing = isReplacing;
        this->_newState = std::move(newState);
    }

    // Marks the current state for removal
    void StateController::RemoveState() {
        this->_isRemoving = true;
    }

    // Processes state changes: add, remove, or replace states as needed
    void StateController::ProcessStateChanges() {
        // Handle state removal
        if (this->_isRemoving && !this->_states.empty()) {
            this->_states.pop();

            if (!this->_states.empty()) {
                this->_states.top()->Resume();
            }
            this->_isRemoving = false;
        }

        // Handle state addition
        if (this->_isAdding) {
            if (!this->_states.empty()) {
                if (this->_isReplacing) {
                    this->_states.pop();
                } else {
                    this->_states.top()->Pause();
                }
            }
            this->_states.push(std::move(this->_newState));
            this->_states.top()->Init();
            this->_isAdding = false;
        }
    }

    // Returns the active state
    StageRef& StateController::GetActiveState() {
        return this->_states.top();
    }
}
