set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../include/${CMAKE_PROJECT_NAME})
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR})

# Files
set(FILES_HEADER
        ${INCROOT}/ResourceControl/ResourceControl.hpp
        ${INCROOT}/ResourceControl/ResourceExceptions.hpp
        ${INCROOT}/ResourceControl/ResourceHolder.hpp
        ${INCROOT}/ResourceControl/ResourceIdentifiers.hpp
        ${INCROOT}/ResourceControl/ResourceLoader.hpp
        ${INCROOT}/ResourceControl/SFMLClassLoaderMakers.hpp

        ${INCROOT}/StateControl/State.hpp
        ${INCROOT}/StateControl/MenuState.hpp
        ${INCROOT}/StateControl/StateControl.hpp
        ${INCROOT}/StateControl/StateIdentifiers.hpp

        ${INCROOT}/Util/Assertion.hpp
        ${INCROOT}/Util/Logger.hpp
        ${INCROOT}/Util/Util.hpp

        ${INCROOT}/Application.hpp
        ${INCROOT}/ApplicationTime.hpp
        ${INCROOT}/defines.hpp
        ${INCROOT}/GlobalColours.hpp
   )

set(FILES_SRC
        ${SRCROOT}/StateControl/State.cpp
        ${SRCROOT}/StateControl/MenuState.cpp
        ${SRCROOT}/StateControl/StateControl.cpp

        ${SRCROOT}/Util/Logger.cpp

        ${SRCROOT}/Application.cpp
        ${SRCROOT}/ApplicationTime.cpp
        ${SRCROOT}/main.cpp
   )

add_executable(${EXECUTABLE_NAME} ${FILES_HEADER} ${FILES_SRC})
target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBS})

