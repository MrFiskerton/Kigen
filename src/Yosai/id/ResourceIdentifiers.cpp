//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 30.05.2020.
//

#include <Yosai/id/ResourceIdentifiers.hpp>
#include <vector>
#include <Kigen/utils/Utils.hpp>

namespace {
    template<typename T>
    struct Type { typedef T type; };

    template<typename T>
    class NameHolder {
    public:
        explicit NameHolder(std::size_t size): m_registry(size) {}

        void insert(T t, const std::string &str) { m_registry[t] = str; }

        const std::string &operator[](T t) {
            auto index = static_cast<std::size_t>(t);
            assertion(index < m_registry.size(), "No match found");
            return m_registry[index];
        }
    private:
        std::vector<std::string> m_registry;
    };

    std::string make_path(const std::string& root, const std::string& name, const std::string& extension){
        return root + name + extension;
    }

    NameHolder<Textures::ID> init(Type<Textures::ID>) {
        NameHolder<Textures::ID> holder(Textures::ID::SIZE);
        const std::string root = "../assets/textures/";
        const std::string file_extension = ".jpg";
#define INSERT_ID(identifier) holder.insert(Textures::ID::identifier, make_path(root, #identifier, file_extension))
        INSERT_ID(water);
#undef INSERT_ID
        return holder;
    }

    template<typename T>
    NameHolder<T> &instance() {
        static auto instance = init(Type<T>());
        return instance;
    }
}

namespace Textures {
    const std::string &path(ID id) { return instance<ID>()[id]; }
}