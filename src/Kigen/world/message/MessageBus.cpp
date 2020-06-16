//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 07.06.2020.
//

#include "Kigen/world/message/MessageBus.hpp"

namespace kigen {
    void MessageBus::push(const Message &message) {
        m_deferred_messages.push(message);
    }

    bool MessageBus::poll(Message &message) {
        if (is_empty()) return false;
        message = m_messages.front();
        m_messages.pop();
        return true;
    }

    bool MessageBus::is_empty() {
        bool empty = m_messages.empty();
        if (empty) {
            std::swap(m_deferred_messages, m_messages);
        }
        return empty;
    }
}