//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 04.06.2020.
//

#ifndef YOSAI_DRAWABLECOMPONENT_HPP
#define YOSAI_DRAWABLECOMPONENT_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "Component.hpp"
#include <Kigen/utils/locator/Locator.hpp>
#include <Kigen/utils/Palette.hpp>

namespace kigen {
class DrawableComponent : public Component, public sf::Drawable/*, public sf::Transformable*/ {
    public:
        using Ptr = std::unique_ptr<DrawableComponent>;
    };
}
#endif //YOSAI_DRAWABLECOMPONENT_HPP
