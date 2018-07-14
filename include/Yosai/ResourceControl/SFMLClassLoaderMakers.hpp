//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 14.07.18.
//

#ifndef INCLUDED_SFMLCLASSLOADERMAKERS_HPP
#define INCLUDED_SFMLCLASSLOADERMAKERS_HPP

#include "ResourceLoader.hpp"

namespace {
    template<class Resource, typename Function>
    ResourceLoader<Resource> makeResourceLoader(const Function &load_function, const std::string &info) {
        auto loader = [=]() -> std::unique_ptr<Resource> {
            std::unique_ptr<Resource> resource(new Resource());
            bool load_success = load_function(*resource);
            //return (load_success ? resource : nullptr);
            if (load_success) return resource;
            return nullptr;
        };

        return ResourceLoader<Resource>(loader, info);
    }
}

template<class Resource, typename ... Args>
ResourceLoader<Resource> loadFromFile(const std::string &filename, Args &&... args) {
    return makeResourceLoader<Resource>(
            [=](Resource &resource) {
                return resource.loadFromFile(filename, std::forward<Args>(args)...);
            }, filename);
}

#endif //INCLUDED_SFMLCLASSLOADERMAKERS_HPP
