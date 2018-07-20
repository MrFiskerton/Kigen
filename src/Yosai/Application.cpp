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
            process_events();
            update_logic(TIME_PER_FRAME);
        }
        update_graphics();
        render();
    }
}

bool Application::is_runing() {
    return m_renderWindow.isOpen() && !m_stateControl.isEmpty();
}

void Application::process_arguments(int argc, char **argv) {

}

void Application::load_configuration() {


    init_resource_control();
    init_render_things();
    init_state_control();
}

void Application::process_events() {
    m_inputControl.poll_events(m_renderWindow);

    if (m_inputControl.isKeyJustPressed(sf::Keyboard::Escape)) m_renderWindow.close();
   /* if (event.type == sf::Event::Closed) {
        m_renderWindow.close();
    }*/

    /*for(int i = static_cast<int>(sf::Keyboard::Unknown) + 1; i < static_cast<int>(sf::Keyboard::KeyCount); i++) {
        static sf::Keyboard::Key  key;

        key = static_cast<sf::Keyboard::Key>(i);

        if (m_inputControl.isKeyJustPressed(key))
            Logger::log() << "Pressed " << Conversion::to_string(key) << Logger::endl;
        if (m_inputControl.isKeyJustReleased(key))
            Logger::log() << "Released " << Conversion::to_string(key) << Logger::endl;
        if (m_inputControl.isKeyPressed(key)) {
            Logger::log() << "Realtime pressed " << Conversion::to_string(key) << Logger::endl;
            while (m_inputControl.isKeyPressed(key)) {}
        }
    }*/

}

void Application::update_logic(const sf::Time &deltaTime) {

}

void Application::update_graphics() {
    m_renderTexture.clear();
    m_stateControl.draw(m_renderTexture);
    m_renderTexture.display();
}

void Application::render() {
    m_renderWindow.clear();
    m_renderWindow.draw(m_canvas_sprite);

    //--
    sf::CircleShape shape(80.f);
    m_inputControl.isButtonPressed(sf::Mouse::Button::Left) ? shape.setFillColor(sf::Color::Blue): shape.setFillColor(sf::Color::Red);
    m_renderWindow.draw(shape);
    //--

    m_renderWindow.display();
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
    m_renderWindow.setFramerateLimit(60);

    const sf::Image& icon = images[Images::icon];
    m_renderWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    m_canvas_sprite.setTexture(m_renderTexture.getTexture());
}

