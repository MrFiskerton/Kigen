//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 13.07.18.
//

#include <Yosai/Util/Logger.hpp>

const Logger::Level Logger::INFO   ("[INFO]:", LogColour::NoColor);
const Logger::Level Logger::WARNING("[WARN]:",  LogColour::Yellow);
const Logger::Level Logger::ERROR  ("[ERROR]:", LogColour::Red);
const Logger::Level Logger::DEBUG_ ("[DEBUG]:", LogColour::Blue);

const std::string Logger::endl(LogColour::NoColor + "\n");

std::ostream& Logger::s_logstr = std::cout;

void Logger::log(Logger::Level level, const std::string &source, const std::string &message) {
#ifdef DEBUG_LOG_ENABLE
    s_logstr << level << ":[" << source << "]: " << message << LogColour::NoColor <<std::endl;
#endif
}

void Logger::log(const std::string& message, const std::string& colour) {
#ifdef DEBUG_LOG_ENABLE
    s_logstr << colour << message << LogColour::NoColor << std::endl;
#endif
}

std::ostream& Logger::log(Logger::Level level, const std::string &source) {
#ifndef DEBUG_LOG_ENABLE
    //
#endif
    auto where = (source =="-//-") ? " " : (":[" + source + "]: ");
    return ( s_logstr << level << where);
}

std::ostream& Logger::log(const std::string& colour) {
#ifndef DEBUG_LOG_ENABLE
    //
#endif
    return (s_logstr << colour);
}

const std::string& Logger::endlF() {
    s_logstr.flush();
    return endl;
}

void Logger::flush() {
    s_logstr.flush();
}
