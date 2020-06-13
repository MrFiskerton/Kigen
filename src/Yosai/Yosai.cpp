//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 23.02.19.
//

#include "Yosai/Yosai.hpp"

using namespace kigen;
using sf::Texture;
using sf::Font;

Yosai::Yosai() {
    ImGui::SFML::Init(m_window);

    init_services();
    init_resources();
    init_actions();
    init_state_control();
}

Yosai::~Yosai() {
    ImGui::SFML::Shutdown();
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
    //ImGui::SFML::Update(m_window, delta);
    //ImGui::EndFrame();
}

//#include "../../cmake-build-debug/_deps/imgui-src/imgui_demo.cpp"
void Yosai::invoke_immediate_GUI() {
    UI::helper(&UI::status::is_open_helper);
    UI::simple_overlay(&UI::status::is_open_simple_overlay);
    //ImGui::ShowDemoWindow();
}

void Yosai::update_graphics() {
    ImGui::SFML::Update(m_window, sf::seconds(1.f/60)); //TODO
    //ImGui::NewFrame();  // Нужно так как в update_logic его закрыли

    invoke_immediate_GUI();

    BasicApplication::update_graphics();
    ImGui::SFML::Render(m_rtexture);
}

namespace {
    void load_textures(TextureHolder& holder) {
        using namespace Textures;
        for(std::size_t id = ID::blue_star; id < ID::SIZE; id++) {
            holder.register_resource(id, loadFromFile<Texture>(path(static_cast<ID>(id))));
        }
    }

    void load_fonts(FontHolder& holder) {
        using namespace Fonts;
        holder.register_resource(TolkienCyr, loadFromFile<Font>(path(TolkienCyr)));
        holder.register_resource(DigitalDisplay, loadFromFile<Font>(path(DigitalDisplay)));
    }
}

void Yosai::init_resources() {
    load_textures(m_resources.texture());
    load_fonts(m_resources.font());
}

void Yosai::update_input() {
    static sf::Event event;
    while (m_window.pollEvent(event)) {
        m_input.push(event);
        ImGui::SFML::ProcessEvent(event);
    }
}
