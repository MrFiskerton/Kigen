set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../include/Kigen)
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR})

# Files
set(FILES_HEADER
    #[[
    ${INCROOT}/action/detail/ActionControl.inl
    ${INCROOT}/action/detail/ActionExpression.hpp
    ${INCROOT}/action/detail/ActionMap.inl
    ${INCROOT}/action/Action.hpp
    ${INCROOT}/action/ActionControl.hpp
    ${INCROOT}/action/ActionMap.hpp
    #]]

    ${INCROOT}/application/DefaultApplicationLoop.hpp
    ${INCROOT}/application/BasicApplication.hpp
    ${INCROOT}/application/ApplicationClock.hpp
    ${INCROOT}/application/IApplication.hpp

    ${INCROOT}/conversion/to_string.hpp

    ${INCROOT}/graphics/Window.hpp

    ${INCROOT}/input/DeviceBuffer.hpp
    ${INCROOT}/input/EventBuffer.hpp
    ${INCROOT}/input/Keyboard.hpp
    ${INCROOT}/input/Mouse.hpp
    ${INCROOT}/input/Window.hpp

    ${INCROOT}/resource/ResourceControl.hpp
    ${INCROOT}/resource/ResourceExceptions.hpp
    ${INCROOT}/resource/ResourceHolder.hpp
    ${INCROOT}/resource/ResourceLoader.hpp
    ${INCROOT}/resource/SFML_LoaderMakers.hpp

    ${INCROOT}/service/impl/ServiceCamera.hpp
    ${INCROOT}/service/interface/ICamera.hpp
    ${INCROOT}/service/interface/IService.hpp

    ${INCROOT}/service/Locator.hpp
    ${INCROOT}/service/Locator.inl
    ${INCROOT}/service/NullService.hpp
    ${INCROOT}/service/Services.hpp

    ${INCROOT}/service/Services.hpp

    #${INCROOT}/state/detail/StateControl.inl
    ${INCROOT}/state/State.hpp
    ${INCROOT}/state/StateControl.hpp

    ${INCROOT}/utils/Assertion.hpp
    ${INCROOT}/utils/Logger.hpp
    ${INCROOT}/utils/NonCopyable.hpp
    ${INCROOT}/utils/NonMovable.hpp
    ${INCROOT}/utils/StopWatch.hpp
    ${INCROOT}/utils/Type.hpp
    ${INCROOT}/utils/Utils.hpp

    ${INCROOT}/defines.hpp
    )

set(FILES_SRC
    #[[
    ${SRCROOT}/action/detail/ActionExpression.cpp
    ${SRCROOT}/action/Action.cpp
    #]]

    ${SRCROOT}/application/ApplicationClock.cpp
    ${SRCROOT}/application/BasicApplication.cpp

    ${SRCROOT}/conversion/to_string.cpp

    ${SRCROOT}/graphics/Window.cpp

    ${SRCROOT}/input/EventBuffer.cpp
    ${SRCROOT}/input/Keyboard.cpp
    ${SRCROOT}/input/Mouse.cpp
    ${SRCROOT}/input/Window.cpp

    ${SRCROOT}/service/Locator.cpp
    ${SRCROOT}/service/NullService.cpp
    ${SRCROOT}/service/ServiceCamera.cpp

    ${SRCROOT}/state/State.cpp
    ${SRCROOT}/state/StateControl.cpp

    ${SRCROOT}/utils/Logger.cpp
    ${SRCROOT}/utils/StopWatch.cpp
    )

add_library(kigen STATIC ${FILES_HEADER} ${FILES_SRC})


