//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 13.07.18.
//

#ifndef INCLUDED_ASSERTION_HPP
#define INCLUDED_ASSERTION_HPP

#include <exception>
#include <string>
#include <sstream>
#include <iostream>

#include "Logger.hpp"

namespace {
    class StreamFormatter {
    public:
        operator std::string() const {
            return stream.str();
        }

        template<typename T>
        StreamFormatter &operator<<(const T &value) {
            stream << value;
            return *this;
        }

    private:
        std::ostringstream stream;
    };

#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wunused-function"
    void assertion_failure(const char *expression, const char *file, int line, const std::string &message) {
        std::ostringstream outputStream;
        if (!message.empty()) {
            outputStream << message << " : \n";
        }

        std::string expressionString(expression);
        if (expressionString == "false" || expressionString == "0" || expressionString == "FALSE") {
            outputStream << "Unreachable code assertion";
        } else {
            outputStream << "Assertion '" << expression << "'";
        }

        outputStream << " failed in file '" << file << "' line " << line;
        std::string report = outputStream.str();
#ifdef DEBUG_LOG_ENABLE
        Logger::error() << report << Logger::endlf();
#else
        std::cerr << report << std::endl;
#endif
        abort();
    }
#   pragma GCC diagnostic pop
}

#ifndef NDEBUG
/*! Assert that EXPRESSION evaluates to true, otherwise abort with associated MESSAGE
    (which may use C++ stream-style message formatting) */
#   define assertion(EXPRESSION, MESSAGE)\
        if(!(EXPRESSION)) {\
            assertion_failure(#EXPRESSION, __FILE__, __LINE__,(StreamFormatter() << (MESSAGE)));\
        }
#else
#   define assertion(EXPRESSION, MESSAGE);
#endif //NDEBUG

#endif //INCLUDED_ASSERTION_HPP
