//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 07.06.2020.
//

#include "Kigen/world/message/Message.hpp"
#include <Kigen/world/physics/Manifold.hpp>

namespace kigen {
    Message::PhysicsEvent::PhysicsEvent(kigen::Manifold *m) : manifold(m) {
        this->event = Collision;
        this->entity_ID[0] = m->A->get_owner_UID();
        this->entity_ID[1] = m->B->get_owner_UID();
    }
}