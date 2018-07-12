//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 12.07.18.
//

#ifndef INCLUDED_STATEIDENTIFIERS_HPP
#define INCLUDED_STATEIDENTIFIERS_HPP

namespace state {
    enum ID : int {
        None = 0,
        Title,
        SplashScreen,
        Menu,
        SingleplayerGame,
        MultiplayerGame,
        Loading,
        Pause,
        Settings,
        GameOver,
        SIZE
    };
}

#endif //INCLUDED_STATEIDENTIFIERS_HPP
