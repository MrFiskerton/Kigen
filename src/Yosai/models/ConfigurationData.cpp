//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 21.07.18.
//

#include <Yosai/structs/ConfigurationData.hpp>

ConfigurationData::ConfigurationData() {
    reset_to_default();
}


void ConfigurationData::reset_to_default() {
    isSoundOn          = true;
    volumeSound        = 30;
    volumeMusic        = 30;

    isVSyncEnabled     = true;
    isFPSLimited       = true;
    FPS_limit          = 60;
    isSmoothing        = true;

    isDebugRendering   = true;
    isDebugRenderingOn = true;
    isDisplayTime      = true;
}
