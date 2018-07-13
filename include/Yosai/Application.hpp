//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 12.07.18.
//

#ifndef INCLUDED_APPLICATION_HPP
#define INCLUDED_APPLICATION_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <Yosai/StateControl/StateControl.hpp>
#include <Yosai/Util/Util.hpp>
#include "ApplicationTime.hpp"

class Application final {
public:
    Application(const Application &) = delete;
    Application &operator=(const Application &) = delete;

    static Application& instance();
    void run();
    bool is_runing();
    void process_arguments(int argc, char *argv[]);
    void load_configuration();

private:
    Application();
    ~Application();

    void process_events();
    void update_logic(const sf::Time &deltaTime);
    void update_graphics();

    void render();
    void init_state_controller();
    void init_render_things();
private:
    static Application s_instance;

    ApplicationTime m_time;
    StateControl m_stateControl;

    sf::RenderWindow   m_renderWindow;
    sf::RenderTexture  m_renderTexture;
    sf::Sprite         m_canvas;

    sf::VideoMode      m_videoMode;
};

#endif //INCLUDED_APPLICATION_HPP
