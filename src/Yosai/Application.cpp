//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 12.07.18.
//

#include "Yosai/Application.hpp"

Application Application::s_instance;

Application::Application() {

}

Application::~Application() {

}

Application &Application::instance() {
    return s_instance;
}

void Application::run() {
    sf::Clock clock;
    sf::Time deltaTime;
    static const std::size_t FRAME_PER_SECOND = 60;
    static const sf::Time TIME_PER_FRAME = sf::seconds(1.f/ FRAME_PER_SECOND);

    while (is_runing()) {
        deltaTime = clock.restart();

        m_time.update(deltaTime);

        while (m_time.m_sinceLastUpdate >= TIME_PER_FRAME) {
            m_time.m_sinceLastUpdate -= TIME_PER_FRAME;
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

}

void Application::process_events() {
    static sf::Event event;
    while (m_renderWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_renderWindow.close();
        } else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape) {//TODO: Delete this
            m_renderWindow.close();
        }
    }
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
    m_renderWindow.draw(m_canvas);
    m_renderWindow.display();
}

void Application::init_state_controller() {

}

void Application::init_render_things() {
    //m_renderTexture.create(INITIAL_WINDOW_RESOLUTION_X, INITIAL_WINDOW_RESOLUTION_Y, INITIAL_COLOR_DEPTH);
    //m_renderTexture.setSmooth(m_configuration.isSmoothing);
    m_canvas.setTexture(m_renderTexture.getTexture());
}