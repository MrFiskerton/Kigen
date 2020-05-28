set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../include/${CMAKE_PROJECT_NAME})
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(LIBS ${LIBS} kigen)

# Files
set(FILES_HEADER
        ${INCROOT}/id/ActionsIdentifiers.hpp
        ${INCROOT}/id/ResourceIdentifiers.hpp
        ${INCROOT}/id/StateIdentifiers.hpp

        ${INCROOT}/models/ConfigurationData.hpp

        ${INCROOT}/states/GameState.hpp
        ${INCROOT}/states/MenuState.hpp
        ${INCROOT}/states/States.hpp

        ${INCROOT}/GlobalColours.hpp
        ${INCROOT}/Yosai.hpp
   )

set(FILES_SRC
        ${SRCROOT}/models/ConfigurationData.cpp

        ${SRCROOT}/states/GameState.cpp
        ${SRCROOT}/states/MenuState.cpp

        ${SRCROOT}/Yosai.cpp
        ${SRCROOT}/main.cpp
    )

add_executable(${EXECUTABLE_NAME} ${FILES_HEADER} ${FILES_SRC})
target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBS})

