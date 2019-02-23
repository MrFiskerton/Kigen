//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 12.07.18.
//

#include <SFML/Graphics/CircleShape.hpp>
#include "Yosai/Application.hpp"

Application::Application() {

}

Application::~Application() {

}

Application &Application::instance() {
    static Application s_instance;
    return s_instance;
}

void Application::run() {
    Logger::notify("Run main loop.");

    static const std::size_t FRAME_PER_SECOND = 60;
    static const sf::Time TIME_PER_FRAME = sf::seconds(1.f / FRAME_PER_SECOND);

    sf::Time time(sf::Time::Zero);

    m_aclock.reset();
    while (is_runing()) {
        time += m_aclock.frame_time();
        while (time >= TIME_PER_FRAME) {
            time -= TIME_PER_FRAME;
            update_input();
            update_logic(TIME_PER_FRAME);
        }
        update_graphics();
        render();
    }
}

void Application::initialize() {
    init_action_control();
    init_input_control();
    init_resource_control();
    init_render_things();
    init_state_control();
}

bool Application::is_runing() {
    return m_renderWindow.isOpen() && !m_stateControl.isEmpty();
}

void Application::process_arguments(int argc, char **argv) {

}

void Application::load_configuration() {
    m_config.reset_to_default();
}

void Application::update_input() {
    //m_inputControl.update(m_renderWindow);
    m_inputControl.clear_events();
    m_action_map.clear_events();

    static sf::Event event;
    while (m_renderWindow.pollEvent(event)) {
        m_inputControl.handle_event(event);
        m_action_map.handle_event(event);
    }

    m_action_map.is_active("test");
}

void Application::update_logic(const sf::Time &deltaTime) {
    m_action_map.invoke_callbacks(m_action_control);
    m_stateControl.update(deltaTime);
}

void Application::update_graphics() {
    m_renderTexture.clear();
    m_stateControl.draw(m_renderTexture);
    m_renderTexture.display();
}

void Application::render() {
    m_renderWindow.clear();
    m_renderWindow.draw(m_canvas_sprite);
    m_renderWindow.display();
}

void kek(int a) {
    Logger::log("Kek") << a << Logger::endlf();
}

void Application::init_action_control() {
    m_action_map["exit"] = Action(sf::Event::Closed) || Action(sf::Keyboard::Escape);
    m_action_map["test"] = (Action(sf::Keyboard::LShift) || Action(sf::Keyboard::RShift)) && Action(sf::Keyboard::J, Action::Released);
    m_action_map["test_2"] = custom_action([&](){ return m_inputControl.isMouseInsedeView(); });

    m_action_control.connect("test", std::bind(&kek, 5));
    m_action_control.connect("test_2", std::bind(&kek, 10));
    m_action_control.connect("exit", [&](){ m_renderWindow.close(); });
}

void Application::init_input_control() {

}

#include <Yosai/States/MenuState.hpp>
void Application::init_state_control() {
    m_stateControl.registerState<MenuState>(States::ID::Menu);

    m_stateControl.forcePushState(States::ID::Menu);
}

void Application::init_resource_control() {
    images.register_resource(Images::icon, loadFromFile<sf::Image>("../resource/default_icon.png"));
}

void Application::init_render_things() {
    m_renderWindow.create({300, 300, 32}, "Yosai", sf::Style::Close);
    m_renderTexture.create(300, 300);
    m_renderWindow.setKeyRepeatEnabled(false);
    m_renderWindow.setVerticalSyncEnabled(m_config.isVSyncEnabled);
    if (m_config.isFPSLimited) m_renderWindow.setFramerateLimit(m_config.FPS_limit);

    const sf::Image& icon = images[Images::icon];
    m_renderWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    m_canvas_sprite.setTexture(m_renderTexture.getTexture());
}

