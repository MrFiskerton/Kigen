//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 13.07.18.
//

#ifndef INCLUDED_RESOURCEHOLDER_HPP
#define INCLUDED_RESOURCEHOLDER_HPP

#include <string>
#include <memory>
#include <unordered_map>

#include "ResourceExceptions.hpp"
#include "ResourceLoader.hpp"
#include <Kigen/utils/Utils.hpp>

template<typename Resource, typename Identifier>
class ResourceHolder: private NonCopyable {
public:
    typedef std::unique_ptr<Resource> ResourcePtr;
    typedef ResourceLoader <Resource> Loader;
public:
    enum KnownIdStrategy : int {
        New,
        Reuse,
        Rewrite
    };
public:
    ResourceHolder() = default;

    ~ResourceHolder() = default;

    ResourceHolder(ResourceHolder &&source) noexcept : m_resourse_map(std::move(source.m_resourse_map)) {}

    ResourceHolder &operator=(ResourceHolder &&source) noexcept {
        m_resourse_map = std::move(source.m_resourse_map);
        return *this;
    }

#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wreturn-type"
    Resource &register_resource(const Identifier &id, const Loader &loader, KnownIdStrategy strategy = New) {
        if (!contains(id)) return load(id, loader);
        switch (strategy) {
            case New:
                throw resource_access_error("Failed to load resource, id have already been reserved.");
            case Reuse:
                return at(id);//TODO
            case Rewrite:
                erase(id);
                return load(id, loader);
            default:
                assertion(false, "Reached default statement");
        }
    }
#   pragma GCC diagnostic pop

    bool remove(const Identifier &id) {
        if (!contains(id)) return false;
        erase(id);
        return true;
    }

    void clear() {
        m_resourse_map.clear();
    }

    bool contains(const Identifier &id) const {
        return m_resourse_map.find(id) != m_resourse_map.end();
    }

    Resource &at(const Identifier &id) const {
        auto it = m_resourse_map.find(id);

        if (it == m_resourse_map.end()) { /* Id does not contain */
            throw resource_access_error("No such m_stateId in the ResourceHolder.");
        }
        return *(it->second);
    }
public:
    const Resource &operator[](const Identifier &id) const { return at(id); }
private:
    Resource &load(const Identifier &id, const Loader &loader) {
        assertion(m_resourse_map.find(id) == m_resourse_map.end(), "id is used");

        ResourcePtr resource = loader.load();
        if (!resource) {
            throw resource_loading_error("ResourceHolder failed to load resource " + loader.info() + "\"");
        }

        auto inserted = m_resourse_map.emplace(id, std::move(resource));
        if (!inserted.second) {
            throw std::runtime_error("Impossible to emplace in map. Resource: " + loader.info());
        }
        Logger::info("ResourceHolder::load") << "Successful load \"" << loader.info() << "\"." << Logger::endl;
        return *(inserted.first->second);
    }

    void erase(const Identifier &id) {
        assertion(contains(id), "id does not contain. And can't be erased");
        auto const &it = m_resourse_map.find(id);
        m_resourse_map.erase(it);
        Logger::info("ResourceHolder::erase") << "Releasing resource by m_stateId = " << id << Logger::endl;
    }

private:
    std::unordered_map<Identifier, ResourcePtr> m_resourse_map;
};

#endif //INCLUDED_RESOURCEHOLDER_HPP
