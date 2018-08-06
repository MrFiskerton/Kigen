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
#include <Yosai/ResourceControl/ResourceControl.hpp>
#include <Yosai/StateControl/StateControl.hpp>
#include <Yosai/Util/Util.hpp>
#include <Yosai/Time/ApplicationClock.hpp>
#include <Yosai/InputControl/InputControl.hpp>
#include <Yosai/Structs/ConfigurationData.hpp>
#include <Yosai/ActionControl/ActionMap.hpp>

class Application: public NonCopyable {
public:
    static Application& instance();
    void run();
    void initialize();
    bool is_runing();
    void process_arguments(int argc, char *argv[]);
    void load_configuration();

private:
    Application();
    ~Application();

    void update_input();
    void update_logic(const sf::Time &deltaTime);
    void update_graphics();

    void render();
    void init_action_control();
    void init_input_control();
    void init_resource_control();
    void init_state_control();
    void init_render_things();
private:
    ApplicationClock m_aclock;
    StateControl m_stateControl;
    InputControl m_inputControl;

    ConfigurationData m_config;

    sf::RenderWindow   m_renderWindow;
    sf::RenderTexture  m_renderTexture;
    sf::Sprite         m_canvas_sprite;

    sf::VideoMode      m_videoMode;

    ResourceHolder<sf::Image, Images::ID> images;//Temporary

    ActionMap<std::string> m_action_map; // Temporary
    ActionContol<std::string> m_action_control; // Temporary
};

#endif //INCLUDED_APPLICATION_HPP
