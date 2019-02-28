//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 25.02.19.
//

#include "Kigen/application/BasicApplication.hpp"

namespace kigen {
    BasicApplication::BasicApplication() {
        init_services();
    }

    bool kigen::BasicApplication::is_runing() const {
        return m_window.isOpen() && !m_state_control.isEmpty();
    }

    void kigen::BasicApplication::update_input() {

    }

    void kigen::BasicApplication::update_logic(const sf::Time &deltaTime) {
        m_state_control.update(deltaTime);
    }

    void kigen::BasicApplication::update_graphics() {

    }

    void kigen::BasicApplication::render() {

    }

    void BasicApplication::init_services() {
        Locator::registrate<ICamera>();

        Locator::locate<ICamera>().test();
        
        Camera camera;
        Locator::provide<ICamera>(&camera);
        Locator::locate<ICamera>().test();

        Locator::provide<ICamera>(nullptr);
        Locator::locate<ICamera>().test();
    }
} // namespace kigen