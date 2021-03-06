#include "Locator.hpp"

namespace kigen {

template<class T>
void Locator::registrate() {
    if (is_registered<T>()) return;
    m_services.push_back(locator::null_service<T>());
    if (m_services.back()) m_services.back()->start_up();
    assertion((service_registrator::id<T>() + 1) == m_services.size(), "Incorrect locator registration");
    Logger::info("Locator::registrate") << "Registration complite. id:= " << service_registrator::id<T>()
                                        << " typeid:= \"" << typeid(T).name() << "\"" << Logger::endl;
}

template<class T>
void Locator::provide(T *service) {
    assertion(is_registered<T>(), "Unregistered locator! Please use \"registrate\" before providing.");

    std::string action;
    std::size_t id = service_registrator::id<T>();

    if (m_services[id]) m_services[id]->shut_down();

    if (service == nullptr) {
        action = "Revert to null ";
        m_services[id] = locator::null_service<T>();
    } else {
        action = "Provide ";
        m_services[id] = service;

    }
    m_services[id]->start_up();
    Logger::info("Locator::insert") << action << "locator with typeid:= " << typeid(T).name()
                                     << " and registration:= " << id << Logger::endlf();
}

template<class T>
T &Locator::locate() {
    assertion(is_registered<T>(), "Unregistered locator! Please use \"registrate\" it.");
    std::size_t id = service_registrator::id<T>();
    assertion(m_services[id] != nullptr,
              "Would be a SIGSEGV. Attempt to insert null locator without an implementation. So will return nullptr.");
    auto ref = dynamic_cast<T *>(m_services[id]);
    assertion(ref != nullptr, "Dynamic cast (typeid:= \"" << typeid(T).name() << "\", id:= " << id << ") FAILED");
    return *ref;
}

template<class T>
bool Locator::is_registered() {
    std::size_t size = m_services.size();
    std::size_t id = service_registrator::id<T>(); // count from 0
    return id < size;
}

}// namespace kigen