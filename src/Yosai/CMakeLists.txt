set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../include/Yosai)
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(LIBS sfml-graphics sfml-window sfml-system sfml-audio)
#set(LIBS SFML::graphics SFML::window SFML::system SFML::audio)
set(LIBS ${LIBS} kigen)
set(LIBS ${LIBS} ImGui-SFML)

# Files
set(FILES_HEADER
        ${INCROOT}/id/ActionsIdentifiers.hpp
        ${INCROOT}/id/ResourceIdentifiers.hpp
        ${INCROOT}/id/StateIdentifiers.hpp

        ${INCROOT}/models/ConfigurationData.hpp
        ${INCROOT}/models/Materials.hpp

        ${INCROOT}/states/GameState.hpp
        ${INCROOT}/states/MenuState.hpp
        ${INCROOT}/states/States.hpp

        ${INCROOT}/ui/Helper_UI.hpp

        ${INCROOT}/GlobalColours.hpp
        ${INCROOT}/Yosai.hpp
   )

set(FILES_SRC
        ${SRCROOT}/id/ResourceIdentifiers.cpp

        ${SRCROOT}/models/ConfigurationData.cpp

        ${SRCROOT}/states/GameState.cpp
        ${SRCROOT}/states/MenuState.cpp

        ${SRCROOT}/Yosai.cpp
        ${SRCROOT}/main.cpp
    )

add_executable(Yosai ${FILES_HEADER} ${FILES_SRC})
target_link_libraries(Yosai ${LIBS})

