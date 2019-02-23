//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 14.07.18.
//

#ifndef INCLUDED_NONMOVABLE_HPP
#define INCLUDED_NONMOVABLE_HPP

struct NonMovable {
    NonMovable() = default;
    NonMovable &operator=(NonCopyable &&) = delete;
    NonMovable(NonCopyable &&) = delete;
};

#endif //INCLUDED_NONMOVABLE_HPP
