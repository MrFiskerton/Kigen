//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 23.02.19.
//

#ifndef INCLUDED_KIGEN_DEFAULTAPPLICATIONLOOP_HPP
#define INCLUDED_KIGEN_DEFAULTAPPLICATIONLOOP_HPP

#include "IApplication.hpp"
#include "ApplicationClock.hpp"
#include <Kigen/utils/Logger.hpp>

namespace kigen {
    struct DefaultApplicationLoop {
        explicit DefaultApplicationLoop() = default;

        void operator()(IApplication &app) const {
            static const std::size_t FRAME_PER_SECOND = 60;
            static const sf::Time TIME_PER_FRAME = sf::seconds(1.f / FRAME_PER_SECOND);

            sf::Time time(sf::Time::Zero);
            ApplicationClock clock;

            Logger::notify("Run default main loop.");
            clock.reset();
            while (app.is_runing()) {
                time += clock.frame_time();
                while (time >= TIME_PER_FRAME) {
                    time -= TIME_PER_FRAME;
                    app.update_input();
                    app.update_logic(TIME_PER_FRAME);
                }
                app.update_graphics();
                app.render();
            }
            Logger::notify("Finish default main loop.");
        }
    };

    const DefaultApplicationLoop default_loop;
} // namespace kigen
#endif //INCLUDED_KIGEN_DEFAULTAPPLICATIONLOOP_HPP
