//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 25.02.19.
//

#ifndef YOSAI_BASICAPPLICATION_HPP
#define YOSAI_BASICAPPLICATION_HPP

#include <Kigen/state/StateControl.hpp>
#include <Kigen/render/Window.hpp>
#include "DefaultApplicationLoop.hpp"
#include "IApplication.hpp"

namespace kigen {
    class BasicApplication : public IApplication {
    public:
        bool is_runing() const override;

    private:
        void update_input() override;

        void update_logic(const sf::Time &deltaTime) override;

        void update_graphics() override;

        void render() override;

        void init_services();

    protected:
        virtual void init_state_control() = 0;

    protected:
        Window* m_window;
        StateControl m_state_control;
    };
} //namespace kigen

#endif //YOSAI_BASICAPPLICATION_HPP
