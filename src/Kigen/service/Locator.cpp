//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 27.02.19.
//

#include <Kigen/service/Locator.hpp>

namespace kigen {
    std::vector<IService *> Locator::m_services;
    std::size_t Locator::service_registrator::counter = 0;
} // namespace kigen