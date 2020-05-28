//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 21.07.18.
//

#ifndef INCLUDED_CONFIGURATIONDATA_HPP
#define INCLUDED_CONFIGURATIONDATA_HPP


#include <SFML/Window.hpp>

struct ConfigurationData final {
public:
    // Sound
    bool isSoundOn;
    int  volumeSound;
    int  volumeMusic;

    // Paths
    std::string    configPath;
    std::string    dataPath;
    std::string    screenshotsPath;
    std::string    screenShotFormat;

    // WindowStatus
    unsigned int   resolution_X;
    unsigned int   resolution_Y;
    unsigned int   colorDepth;
    bool           isVSyncEnabled;
    bool           isFPSLimited;
    unsigned int   FPS_limit;
    bool           isSmoothing;
    //DisplayMode displayMode;

    // InputControl
    //std::map<Key, sf::Keyboard::Key> mainKeyMap;

    // Debug
    bool isDebugRendering;
    bool isDebugRenderingOn;

    // Misc
    bool           isDisplayTime;
    float          gameSpeed;
public:
    ConfigurationData();
public:
    void reset_to_default();
};


#endif //INCLUDED_CONFIGURATIONDATA_HPP
