//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 14.07.18.
//

#ifndef INCLUDED_RESOURCELOADER_HPP
#define INCLUDED_RESOURCELOADER_HPP

#include <functional>
#include <memory>
#include <string>

template<class Resource>
class ResourceLoader {
public:
    typedef std::unique_ptr<Resource> ResourcePtr;
    typedef std::function<ResourcePtr()> Loader;
public:
    ResourceLoader(Loader loader, std::string info) : m_loader(std::move(loader)), m_info(std::move(info)) {}

    ResourcePtr load() const { return m_loader();  }

    const std::string& info() const { return m_info; }

private:
    Loader m_loader;
    std::string m_info;
};

#endif //INCLUDED_RESOURCELOADER_HPP
