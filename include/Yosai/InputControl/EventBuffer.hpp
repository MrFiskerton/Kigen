//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 19.07.18.
//

#ifndef INCLUDED_EVENTBUFFER_HPP
#define INCLUDED_EVENTBUFFER_HPP


#include <SFML/Window.hpp>

class EventBuffer {
public:
    EventBuffer();

    // Modifiers
    void push(const sf::Event &event);
    void clear();
    void poll_events(sf::Window &window);

    // Accessors
    bool contains(const sf::Event &event) const;
    bool filter(const sf::Event &filter_event, std::vector<sf::Event> &out) const;
    
private:
    // Note: Since there are at most a few dozens of events per frame (at a decent framerate not even that),
    // std::vector and linear search is fine

    std::vector<sf::Event> m_buffer;
};


#endif //INCLUDED_EVENTBUFFER_HPP
