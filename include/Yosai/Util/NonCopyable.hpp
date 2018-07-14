//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 14.07.18.
//

#ifndef INCLUDED_NONCOPYABLE_HPP
#define INCLUDED_NONCOPYABLE_HPP

struct NonCopyable {
    NonCopyable() = default;
    NonCopyable &operator=(const NonCopyable &) = delete;
    NonCopyable(const NonCopyable &) = delete;
};

#endif //INCLUDED_NONCOPYABLE_HPP
