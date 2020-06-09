//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 07.06.2020.
//

#ifndef YOSAI_MESSAGEBUS_HPP
#define YOSAI_MESSAGEBUS_HPP

#include <Kigen/utils/NonCopyable.hpp>
#include <functional>
#include <vector>
#include <queue>
#include "Message.hpp"

namespace kigen {
    class MessageBus: private NonCopyable {
    public:
        void push(const Message& message);
        bool poll(Message& message);
       // void send_immediate(const Message& message);
       // void add_receiver(std::size_t topic, std::function<void (const Message&)>);
    private:
        bool is_empty();
    private:
        std::queue<Message> m_messages;
        std::queue<Message> m_deferred_messages;
    };
}


#endif //YOSAI_MESSAGEBUS_HPP
