//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 18.07.18.
//

#include <Kigen/input/AbstractDevice.hpp>

AbstractDevice::AbstractDevice(): is_action_locked(false) {

}

void AbstractDevice::lock() {
    is_action_locked = true;
}

void AbstractDevice::unlock() {
    is_action_locked = false;
}

bool AbstractDevice::is_locked() const {
    return is_action_locked;
}
