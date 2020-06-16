//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 07.06.2020.
//

#ifndef KIGEN_MESSAGE_HPP
#define KIGEN_MESSAGE_HPP

//#include <Kigen/world/physics/Manifold.hpp>
#include <SFML/Config.hpp>

namespace kigen {
    class Manifold;
    struct Message {
        enum Type {
            Audio = 1, Drawable, Logic, Physics, Entity, UI, Player
        } type;

        struct PhysicsEvent {
            enum { Collision } event;
            sf::Uint64 entity_ID[2];

            //explicit PhysicsEvent(Manifold* m);
        };

        bool is(Type t) const { return type == t;}

        union {
            PhysicsEvent physics;
        };
    };
}

#endif //KIGEN_MESSAGE_HPP
