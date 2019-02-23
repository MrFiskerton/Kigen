//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 18.07.18.
//

#include <Kigen/input/AbstractDeviceController.hpp>

AbstractDeviceController::AbstractDeviceController(): is_action_locked(false) {

}

void AbstractDeviceController::lock_action() {
    is_action_locked = true;
}

void AbstractDeviceController::unlock_action() {
    is_action_locked = false;
}

bool AbstractDeviceController::is_locked() const {
    return is_action_locked;
}
