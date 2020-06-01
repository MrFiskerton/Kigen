//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 23.02.19.
//

#include "Yosai/Yosai.hpp"


using namespace kigen;
using sf::Texture;

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
//    ImGui::SFML::Update(m_window, delta); // Не работает, а должно
//    ImGui::EndFrame();
}

void Yosai::update_graphics() {
    ImGui::SFML::Update(m_window, sf::seconds(1.f / 60));

    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");
    ImGui::End();
    //ImGui::ShowTestWindow();


    //BasicApplication::update_graphics();

    m_canvas.setTexture(m_rtexture.getTexture());

    m_rtexture.clear();
    m_state_control.draw(m_rtexture);
    ImGui::SFML::Render(m_rtexture);
    m_rtexture.display();
}

namespace {
    void load_textures(TextureHolder& holder) {
        using namespace Textures;
        for(std::size_t id = ID::blue_star; id < ID::SIZE; id++) {
            holder.register_resource(id, loadFromFile<Texture>(path(static_cast<ID>(id))));
        }
    }
}

void Yosai::init_resources() {
    load_textures(m_resources.texture());
}

void Yosai::update_input() {
    static sf::Event event;
    while (m_window.pollEvent(event)) {
        m_input.push(event);
        ImGui::SFML::ProcessEvent(event);
    }
}
