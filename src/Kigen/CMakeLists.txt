set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../include/Kigen)
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR})

# Files
set(FILES_HEADER
        ${INCROOT}/action/detail/ActionControl.inl
        ${INCROOT}/action/detail/ActionExpression.hpp
        ${INCROOT}/action/detail/ActionMap.inl
        ${INCROOT}/action/Action.hpp
        ${INCROOT}/action/ActionControl.hpp
        ${INCROOT}/action/ActionMap.hpp

        ${INCROOT}/application/DefaultApplicationLoop.hpp
        ${INCROOT}/application/ApplicationClock.hpp
        ${INCROOT}/application/IApplication.hpp

        ${INCROOT}/conversion/Conversion.hpp

        ${INCROOT}/input/AbstractDeviceController.hpp
        ${INCROOT}/input/InputControl.hpp
        ${INCROOT}/input/KeyboardController.hpp
        ${INCROOT}/input/MouseController.hpp
        ${INCROOT}/input/WindowController.hpp

        ${INCROOT}/resource/ResourceControl.hpp
        ${INCROOT}/resource/ResourceExceptions.hpp
        ${INCROOT}/resource/ResourceHolder.hpp
        ${INCROOT}/resource/ResourceLoader.hpp
        ${INCROOT}/resource/SFML_LoaderMakers.hpp

        ${INCROOT}/service/ServiceLocator.hpp

        ${INCROOT}/state/State.hpp
        ${INCROOT}/state/StateControl.hpp

        ${INCROOT}/utils/Assertion.hpp
        ${INCROOT}/utils/Logger.hpp
        ${INCROOT}/utils/NonCopyable.hpp
        ${INCROOT}/utils/NonMovable.hpp
        ${INCROOT}/utils/StopWatch.hpp
        ${INCROOT}/utils/Utils.hpp

        ${INCROOT}/defines.hpp
   )

set(FILES_SRC
        ${SRCROOT}/action/detail/ActionExpression.cpp
        ${SRCROOT}/action/Action.cpp

        ${SRCROOT}/application/ApplicationClock.cpp

        ${SRCROOT}/conversion/KeyConversion.cpp

        ${SRCROOT}/input/AbstractDeviceController.cpp
        ${SRCROOT}/input/InputControl.cpp
        ${SRCROOT}/input/KeyboardController.cpp
        ${SRCROOT}/input/MouseController.cpp
        ${SRCROOT}/input/WindowController.cpp

        ${SRCROOT}/service/ServiceLocator.cpp

        ${SRCROOT}/state/State.cpp
        ${SRCROOT}/state/StateControl.cpp

        ${SRCROOT}/utils/Logger.cpp
        ${SRCROOT}/utils/StopWatch.cpp
   )

add_library(kigen STATIC ${FILES_HEADER} ${FILES_SRC})


