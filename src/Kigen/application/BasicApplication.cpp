//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 25.02.19.
//

#include "Kigen/application/BasicApplication.hpp"

namespace kigen {

BasicApplication::BasicApplication(): m_window(sf::VideoMode(500, 500), "TEST") {
    init_services();
    init_action();
}

bool kigen::BasicApplication::is_runing() const {
    return m_window.isOpen() && !m_state_control.isEmpty();
}

void kigen::BasicApplication::update_input() {
    m_input.update(m_window);
}

void kigen::BasicApplication::update_logic(const sf::Time &deltaTime) {
    m_actions.invoke_callbacks();
    m_state_control.update(deltaTime);
}

void kigen::BasicApplication::update_graphics() {
    m_canvas.setTexture(m_renderTexture.getTexture());

    m_renderTexture.clear();
    m_state_control.draw(m_renderTexture);
    m_renderTexture.display();
}

void kigen::BasicApplication::render() {
    m_window.clear();
    m_window.draw(m_canvas);
    m_window.display();
}

void BasicApplication::init_services() {
    Locator::registrate<ICamera>();

    Locator::locate<ICamera>().test();

    Camera camera;
    Locator::provide<ICamera>(&camera);
    Locator::locate<ICamera>().test();

    Locator::provide<ICamera>(nullptr);
    Locator::locate<ICamera>().test();

    Locator::registrate<InputControl>();
    Locator::provide<InputControl>(&m_input);
}

void BasicApplication::init_action() {
    auto &registry = m_actions.get_registry();

//    registry["Up"] = Action(sf::Keyboard::W, RealTime | Pressed);
//    registry["Down"] = Action(sf::Keyboard::S, RealTime | Pressed);
//    registry["Left"] = Action(sf::Keyboard::A, RealTime | Pressed);
//    registry["Right"] = Action(sf::Keyboard::D, RealTime | Pressed);

    registry["esc"] = Action( [&](){
        return m_input.keyboard().isKeyJustPressed(sf::Keyboard::Escape);
    });

    registry["close_window"] =  registry["esc"] || Action( [&](){ return m_input.window().isClosed(); });

    m_actions.connect("close_window", [&]() { m_window.close(); });

    //
    registry["A"] =  Action( [&](){ return m_input.keyboard().isKeyJustPressed(sf::Keyboard::A); });
    registry["B"] =  Action( [&](){ return m_input.keyboard().isKeyJustPressed(sf::Keyboard::B); });
    registry["A||B"] = registry["A"] || registry["B"];

    m_actions.connect("A", []() { Logger::notify("A"); });
    m_actions.connect("B", []() { Logger::notify("B"); });
    m_actions.connect("A||B", []() { Logger::notify("A||B"); });
//    m_actions.connect("Up", []() { Logger::notify("Up"); });
}

} // namespace kigen