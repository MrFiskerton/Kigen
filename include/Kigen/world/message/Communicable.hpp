//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 07.06.2020.
//

#ifndef YOSAI_COMMUNICABLE_HPP
#define YOSAI_COMMUNICABLE_HPP

#include <cassert>
#include "MessageBus.hpp"

namespace kigen {
    class Communicable {
    public:
        Communicable() = default;
        explicit Communicable(MessageBus& mbus) : m_message_bus(&mbus) {}
        virtual ~Communicable() = default;
        void set_message_bus(MessageBus& mbus) { m_message_bus = &mbus;}
        void send_message(const Message& message) { assert(m_message_bus); m_message_bus->push(message); };
        virtual void receive_message(const Message& message) = 0;
    protected:
        MessageBus* m_message_bus{};
    };
}

#endif //YOSAI_COMMUNICABLE_HPP
