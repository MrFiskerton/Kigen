//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 14.07.18.
//

#include "Yosai/Time/StopWatch.hpp"

StopWatch::StopWatch() : m_running(false), m_clock(), m_elapsed_buffer(sf::Time::Zero) {}

sf::Time StopWatch::elapsed_time() const {
    return m_elapsed_buffer + (m_running ? m_clock.getElapsedTime() : sf::Time::Zero);
}

bool StopWatch::is_running() const {
    return m_running;
}

void StopWatch::start() {
    if (!m_running) {
        m_clock.restart();
        m_running = true;
    }
}

void StopWatch::pause() {
    if (m_running) {
        m_elapsed_buffer += m_clock.getElapsedTime();
        m_running = false;
    }
}

void StopWatch::reset() {
    m_elapsed_buffer = sf::Time::Zero;
    m_running = false;
}

void StopWatch::restart() {
    reset();
    start();
}