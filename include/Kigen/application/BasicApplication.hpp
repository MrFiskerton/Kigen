//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 25.02.19.
//

#ifndef YOSAI_BASICAPPLICATION_HPP
#define YOSAI_BASICAPPLICATION_HPP

#include <Kigen/state/StateControl.hpp>
#include <Kigen/graphics/Window.hpp>
#include <Kigen/utils/locator/Locator.hpp>
#include <Kigen/action/ActionControl.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <Kigen/resource/ResourceControl.hpp>
#include "DefaultApplicationLoop.hpp"
#include "IApplication.hpp"

namespace kigen {

class BasicApplication : public IApplication {
public:
    BasicApplication();

    bool is_runing() const override;

protected:
    void update_input() override;

    void update_logic(const sf::Time &deltaTime) override;

    void update_graphics() override;

    void render() override;

    void init_services();

protected:
    virtual void init_state_control() = 0;

protected:
    sf::RenderWindow   m_window;
    sf::RenderTexture  m_renderTexture;
    sf::Sprite         m_canvas;

    StateControl m_state_control;
    ResourceControl m_resources;
    InputControl m_input;
};

} //namespace kigen

#endif //YOSAI_BASICAPPLICATION_HPP
