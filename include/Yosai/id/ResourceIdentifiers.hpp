//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 13.07.18.
//

#ifndef INCLUDED_RESOURCEIDENTIFIERS_HPP
#define INCLUDED_RESOURCEIDENTIFIERS_HPP

#include <string>

namespace sf {
    class Font;
    class Image;
    class Texture;
    class SoundBuffer;
    class Music;
    class Shader;
}

namespace Fonts {
    enum ID : int {
        TolkienCyr = 0,
        SIZE
    };
    const std::string& path(ID id);
}

namespace Textures {
    enum ID : int {
        blue_star = 0,
        circle_air,
        circle_earth,
        circle_fire,
        circle_water,
        water,
        SIZE
    };

    const std::string& path(ID id);
}

namespace Images {
    enum ID : int {
        icon = 0,
        SIZE
    };
}

namespace Sounds {
    enum ID : int {
        sound_name = 0,
        SIZE
    };
}

namespace Music {
    enum ID : int {
        music_name = 0,
        SIZE
    };
}

namespace Shaders {
    enum ID : int {
        shader_name = 0,
        SIZE
    };
}


#endif //INCLUDED_RESOURCEIDENTIFIERS_HPP
