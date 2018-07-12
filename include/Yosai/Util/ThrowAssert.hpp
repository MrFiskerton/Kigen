//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 13.07.18.
//

#ifndef INCLUDED_THROWASSERT_HPP
#define INCLUDED_THROWASSERT_HPP


#include <exception>
#include <string>
#include <sstream>
#include <iostream>

#include "Logger.hpp"

class AssertionFailureException : public std::exception {
public:
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

public:
    AssertionFailureException(const char *expression, const char *file, int line, const std::string &message)
            : m_expression(expression), m_file(file), m_line(line), m_message(message) {

        std::ostringstream outputStream;
        if (!message.empty()) {
            outputStream << message << ": ";
        }

        std::string expressionString(expression);
        if (expressionString == "false" || expressionString == "0" || expressionString == "FALSE") {
            outputStream << "Unreachable code assertion";
        } else {
            outputStream << "Assertion '" << expression << "'";
        }

        outputStream << " failed in file '" << file << "' line " << line;
        m_report = outputStream.str();
        log_error();
    }

    ~AssertionFailureException() override = default;

    void log_error() {
#ifdef DEBUG_LOG_ENABLE
        Logger::error() << m_report << Logger::endlF();
#else
        std::cerr << m_report << std::endl;
#endif
    }

    const char *what() const noexcept override {
        return m_report.c_str();
    }

    const char *expression() const noexcept {
        return m_expression;
    }

    const char *file() const noexcept {
        return m_file;
    }

    int line() const noexcept {
        return m_line;
    }

    const char *message() const noexcept {
        return m_message.c_str();
    }

private:
    const char* m_expression;
    const char* m_file;
    int m_line;
    std::string m_message;
    std::string m_report;

};

#ifndef NDEBUG
/*! Assert that EXPRESSION evaluates to true, otherwise raise AssertionFailureException with associated MESSAGE
    (which may use C++ stream-style message formatting) */
#   define throw_assert(EXPRESSION, MESSAGE)\
        if(!(EXPRESSION)) {\
            throw AssertionFailureException(#EXPRESSION, __FILE__, __LINE__, \
                                                        (AssertionFailureException::StreamFormatter() << (MESSAGE)));\
        }
#else
#   define throw_assert(EXPRESSION, MESSAGE);
#endif //NDEBUG

#endif //INCLUDED_THROWASSERT_HPP
