//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 02.06.2020.
//

#ifndef YOSAI_YIELD_HPP
#define YOSAI_YIELD_HPP

#define YBegin static int state = 0; switch(state) { case 0:
#define yield(i,x) do { state = __LINE__; return x; \
                         case __LINE__:; } while (0)
#define YEnd }

#endif //YOSAI_YIELD_HPP
