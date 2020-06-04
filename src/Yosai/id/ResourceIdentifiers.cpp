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
        const std::string png = ".png";
        const std::string jpg = ".jpg";
#define INSERT_ID(identifier) holder.insert(Textures::ID::identifier, make_path(root, #identifier, png))
        INSERT_ID(blue_star);
        INSERT_ID(circle_air);
        INSERT_ID(circle_earth);
        INSERT_ID(circle_fire);
        INSERT_ID(circle_water);
#undef INSERT_ID

#define INSERT_ID(identifier) holder.insert(Textures::ID::identifier, make_path(root, #identifier, jpg))
        INSERT_ID(water);
#undef INSERT_ID
        return holder;
    }

    NameHolder<Fonts::ID> init(Type<Fonts::ID>) {
        NameHolder<Fonts::ID> holder(Fonts::ID::SIZE);
        const std::string root = "../assets/fonts/";
        const std::string ttf = ".ttf";
#define INSERT_ID(identifier) holder.insert(Fonts::ID::identifier, make_path(root, #identifier, ttf))
        INSERT_ID(TolkienCyr);
#undef INSERT_ID
        return holder;
    }

    template<typename T>
    NameHolder<T> &instance() {
        static auto instance = init(Type<T>());
        return instance;
    }
}

namespace Textures { const std::string &path(ID id) { return instance<ID>()[id]; } }
namespace Fonts    { const std::string &path(ID id) { return instance<ID>()[id]; } }