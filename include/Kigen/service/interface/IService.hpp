//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 26.02.19.
//

#ifndef YOSAI_ISERVICE_HPP
#define YOSAI_ISERVICE_HPP

#include <memory>
#include <Kigen/utils/Utils.hpp>

namespace kigen {
    class IService {
    public:
        virtual ~IService() = default;
        virtual void start_up() {}
        virtual void shut_down() {}
    };
} // namespace kigen


#endif //YOSAI_ISERVICE_HPP 
