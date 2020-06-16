//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 13.07.18.
//

#ifndef INCLUDED_RESOURCECONTROL_HPP
#define INCLUDED_RESOURCECONTROL_HPP

#include <SFML/Graphics/Texture.hpp>
#include "ResourceHolder.hpp"
#include "SFML_LoaderMakers.hpp"
#include <Kigen/utils/locator/IService.hpp>
#include <SFML/Graphics/Font.hpp>

typedef ResourceHolder<sf::Texture, int> TextureHolder;
typedef ResourceHolder<sf::Font, int> FontHolder;

namespace kigen {

class ResourceControl : public IService {
public:
    TextureHolder& texture() { return m_textures; }
    FontHolder& font() { return m_fonts; }
private:
    TextureHolder m_textures;
    FontHolder m_fonts;
};

} // namespace kigen
#endif //INCLUDED_RESOURCECONTROL_HPP
