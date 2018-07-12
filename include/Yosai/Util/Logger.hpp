//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 13.07.18.
//

#ifndef INCLUDED_LOGGER_HPP
#define INCLUDED_LOGGER_HPP

#if YOSAI_LINUX
#   define COLOR_SUPPORT
#endif

#include <iostream>
#include <fstream>
#include <iomanip>

#include "Yosai/defines.hpp"

namespace LogColour {
#ifdef COLOR_SUPPORT
    const std::string Black   = "\e[30m";
    const std::string Red     = "\e[31m";
    const std::string Green   = "\e[32m";
    const std::string Yellow  = "\e[33m";
    const std::string Blue    = "\e[34m";
    const std::string Magenta = "\e[35m";
    const std::string Cyan    = "\e[36m";
    const std::string White   = "\e[37m";
    const std::string NoColor = "\e[0m";
#else
    const std::string Black   = "";
    const std::string Red     = "";
    const std::string Green   = "";
    const std::string Yellow  = "";
    const std::string Blue    = "";
    const std::string Magenta = "";
    const std::string Cyan    = "";
    const std::string White   = "";
    const std::string NoColor = "";
#endif
}

class Logger final {
public:
    struct Level {
        std::string prefix;
        std::string colour;

        Level(std::string p, std::string c) : prefix(p), colour(c) {}

        friend std::ostream& operator<<(std::ostream& ostr, const Logger::Level& level) {
            ostr << level.colour << level.prefix;
            return ostr;
        }
    };

    static const Level INFO;
    static const Level WARNING;
    static const Level ERROR;
    static const Level DEBUG_;

    static const std::string endl;

public:

    static void log(Logger::Level level, const std::string &source, const std::string &message);
    static void log(const std::string& message, const std::string& colour);

    static void notify(const std::string &message) { log(std::string(">>> ").append(message), LogColour::Cyan);}
    static void info (const std::string &source, const std::string &message) { log(INFO, source, message);}
    static void warn (const std::string &source, const std::string &message) { log(WARNING, source, message);}
    static void error(const std::string &source, const std::string &message) { log(ERROR, source, message);}
    static void debug(const std::string &source, const std::string &message) { log(DEBUG_, source, message);}
    static void debug_once(const std::string &source, const std::string &message) {
        static std::string prev_message;
        if(prev_message != message) { debug(source, message); prev_message = message;}
    }

    static std::ostream& log(const std::string& colour = LogColour::Magenta);
    static std::ostream& log(Logger::Level level, const std::string &source);
    static std::ostream& notify() { return log(LogColour::Cyan); }
    static std::ostream& info (const std::string &source = "-//-") { return log(INFO, source);}
    static std::ostream& warn (const std::string &source = "-//-") { return log(WARNING, source);}
    static std::ostream& error(const std::string &source = "-//-") { return log(ERROR, source);}
    static std::ostream& debug(const std::string &source = "-//-") { return log(DEBUG_, source);}

    static const std::string& endlF();
    static void flush();

    static std::ostream& get_stream() { return s_logstr; }
private:
    Logger() = delete;
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;
private:
    static std::ostream& s_logstr;
};

#endif //INCLUDED_LOGGER_HPP
