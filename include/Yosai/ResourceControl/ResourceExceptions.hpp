//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 13.07.18.
//

#ifndef INCLUDED_RESOURCEEXCEPTIONS_HPP
#define INCLUDED_RESOURCEEXCEPTIONS_HPP

#include <stdexcept>

class resource_loading_error : public std::runtime_error {
public:
    explicit resource_loading_error(const std::string &message) : std::runtime_error(message) {}
};

class resource_access_error : public std::runtime_error {
public:
    explicit resource_access_error(const std::string &message) : std::runtime_error(message) {}
};

#endif //INCLUDED_RESOURCEEXCEPTIONS_HPP
