//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 23.02.19.
//

#include "Yosai/Yosai.hpp"

using namespace kigen;
using sf::Texture;

Yosai::Yosai() {
    init_services();
    init_resources();
    init_actions();
    init_state_control();
}

void Yosai::init_state_control() {
    m_state_control.registerState<MenuState>(States::ID::Menu);
    m_state_control.registerState<GameState>(States::ID::Game);

    m_state_control.forcePushState(States::ID::Game);
}

void Yosai::init_actions() {
    using namespace Actions;
    auto &registry = m_actions.get_registry();

    registry[close_window] = Action(sf::Keyboard::Escape, Released)
                          || Action([&]() { return m_input.window().isClosed(); });

    m_actions.connect(close_window, [&]() { m_window.close(); });
}

void Yosai::init_services() {
    Locator::registrate<InputControl>();
    Locator::registrate<ResourceControl>();
    Locator::registrate<ActionControl<Actions::ID>>();

    Locator::provide<InputControl>(&m_input);
    Locator::provide<ResourceControl>(&m_resources);
    Locator::provide<ActionControl<Actions::ID>>(&m_actions);
}

void Yosai::update_logic(const sf::Time &delta) {
    m_actions.invoke_callbacks();
    BasicApplication::update_logic(delta);
}

void Yosai::update_graphics() {
    BasicApplication::update_graphics();
}

namespace {
    void load_textures(TextureHolder& holder) {
        using namespace Textures;
        holder.register_resource(ID::water, loadFromFile<Texture>(path(ID::water)));
    }
}

void Yosai::init_resources() {
    load_textures(m_resources.texture());
}

void Yosai::update_input() {
    BasicApplication::update_input();
}
