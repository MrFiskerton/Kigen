set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../include/${CMAKE_PROJECT_NAME})
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR})

# Files
set(FILES_HEADER
        ${INCROOT}/ID/ResourceIdentifiers.hpp
        ${INCROOT}/ID/StateIdentifiers.hpp

        ${INCROOT}/ResourceControl/ResourceControl.hpp
        ${INCROOT}/ResourceControl/ResourceExceptions.hpp
        ${INCROOT}/ResourceControl/ResourceHolder.hpp
        ${INCROOT}/ResourceControl/ResourceLoader.hpp
        ${INCROOT}/ResourceControl/SFML_LoaderMakers.hpp

        ${INCROOT}/StateControl/State.hpp
        ${INCROOT}/StateControl/StateControl.hpp

        ${INCROOT}/States/MenuState.hpp

        ${INCROOT}/Time/ApplicationClock.hpp
        ${INCROOT}/Time/StopWatch.hpp

        ${INCROOT}/Util/Assertion.hpp
        ${INCROOT}/Util/Logger.hpp
        ${INCROOT}/Util/NonCopyable.hpp
        ${INCROOT}/Util/NonMovable.hpp
        ${INCROOT}/Util/Util.hpp

        ${INCROOT}/Application.hpp
        ${INCROOT}/defines.hpp
        ${INCROOT}/GlobalColours.hpp
   )

set(FILES_SRC
        ${SRCROOT}/StateControl/State.cpp
        ${SRCROOT}/StateControl/StateControl.cpp

        ${SRCROOT}/States/MenuState.cpp

        ${SRCROOT}/Time/ApplicationClock.cpp
        ${SRCROOT}/Time/StopWatch.cpp

        ${SRCROOT}/Util/Logger.cpp

        ${SRCROOT}/Application.cpp
        ${SRCROOT}/main.cpp
   )

add_executable(${EXECUTABLE_NAME} ${FILES_HEADER} ${FILES_SRC})
target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBS})

