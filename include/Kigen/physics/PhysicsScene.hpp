//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 01.06.2020.
//

#ifndef YOSAI_PHYSICSSCENE_HPP
#define YOSAI_PHYSICSSCENE_HPP

#include <SFML/System/Time.hpp>

namespace kigen {

    class PhysicsScene {
    public:
        enum Layer : unsigned {
            L1 = 0, L2
        };

        void update(float dt);

    private:
        std::vector<Manifold> m_contacts;
    };

}


#endif //YOSAI_PHYSICSSCENE_HPP
