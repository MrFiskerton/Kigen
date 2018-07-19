//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 19.07.18.
//

#include <functional>
#include "Yosai/InputControl/EventBuffer.hpp"

EventBuffer::EventBuffer() : m_buffer() {}

void EventBuffer::push(const sf::Event &event) {
    m_buffer.push_back(event);
}

void EventBuffer::clear() {
    m_buffer.clear();
}

bool EventBuffer::contains(const sf::Event &event) const {
    std::vector<sf::Event> unused;
    return filter(event, unused);
}

bool EventBuffer::filter(const sf::Event &filter_event, std::vector<sf::Event> &out) const {
    // Variable to check if something was actually inserted (don't look at range, it's not filtered yet)
    std::size_t oldSize = out.size();

    // Copy events that fulfill filter criterion to the end of the output vector

//    std::copy_if(m_buffer.begin(), m_buffer.end(), std::back_inserter(out),
//                 [&](const sf::Event &event){ return event == filter_event; });
    return oldSize != out.size();
}

void EventBuffer::poll_events(sf::Window &window) {
    sf::Event event;

    while (window.pollEvent(event))
        push(event);
}
