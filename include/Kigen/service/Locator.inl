#include "Locator.hpp"

namespace kigen {
    template<class T>
    void Locator::registrate() {
        if (is_registered<T>()) return;
        m_services.push_back(null_service<T>());
        assertion((service_registrator::id<T>() + 1) == m_services.size(), "Incorrect service registration");
        Logger::info("Locator::registrate") << "Registration complite. id:= " << service_registrator::id<T>()
                                            << " typeid:= \"" << typeid(T).name() << "\"" << Logger::endl;
    }

    template<class T>
    void Locator::provide(T *service) {
        assertion(is_registered<T>(), "Unregistered service! Please use \"registrate\" before providing.");

        std::string action;
        std::size_t id = service_registrator::id<T>();

        if (m_services[id]) m_services[id]->shut_down();

        if (service == nullptr) {
            action = "Revert to null ";
            m_services[id] = null_service<T>();
        } else {
            action = "Provide ";
            m_services[id] = service;

        }
        m_services[id]->start_up();
        Logger::info("Locator::provide") << action << "service with typeid:= " << typeid(T).name()
                                         << " and registration:= " << id << Logger::endlf();
    }

    template<class T>
    T &Locator::locate() {
        assertion(is_registered<T>(), "Unregistered service! Please use \"registrate\" it.");
        std::size_t id = service_registrator::id<T>();
        assertion(m_services[id] != nullptr,
                  "Would be a SIGSEGV. Attempt to provide null service without an implementation. So will return nullptr.");
        auto ref = dynamic_cast<T *>(m_services[id]);
        assertion(ref != nullptr, "Dynamic cast failed");
        return *ref;
    }

    template<class T>
    bool Locator::is_registered() {
        std::size_t size = m_services.size();
        std::size_t id = service_registrator::id<T>(); // count from 0
        return id < size;
    }
}