//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 06.06.2020.
//

#ifndef YOSAI_NEXT_HPP
#define YOSAI_NEXT_HPP

#include <cstddef>
#include <cassert>

class Next {
public:
    Next(std::size_t from, std::size_t to):from(from), to(to), current(from) { assert(from < to);  }

    std::size_t next() {
        if(current == to) { current = from; return to; }
        return current++;
    }

    operator std::size_t () const { return current; }
private:
    std::size_t from, to, current;
};

#endif //YOSAI_NEXT_HPP
