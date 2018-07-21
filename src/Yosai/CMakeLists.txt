set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../include/${CMAKE_PROJECT_NAME})
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR})

# Files
set(FILES_HEADER
        #${INCROOT}/ActionControl/detail/ActionControl.inl
        #${INCROOT}/ActionControl/detail/ActionMap.inl

        #${INCROOT}/ActionControl/Action.hpp
        #${INCROOT}/ActionControl/ActionControl.hpp
        #${INCROOT}/ActionControl/ActionMap.hpp

        ${INCROOT}/Conversion/Conversion.hpp

        ${INCROOT}/ID/ResourceIdentifiers.hpp
        ${INCROOT}/ID/StateIdentifiers.hpp

        ${INCROOT}/InputControl/AbstractDeviceController.hpp
        ${INCROOT}/InputControl/InputControl.hpp
        ${INCROOT}/InputControl/EventBuffer.hpp
        ${INCROOT}/InputControl/KeyboardController.hpp
        ${INCROOT}/InputControl/MouseController.hpp
        ${INCROOT}/InputControl/WindowController.hpp

        ${INCROOT}/ResourceControl/ResourceControl.hpp
        ${INCROOT}/ResourceControl/ResourceExceptions.hpp
        ${INCROOT}/ResourceControl/ResourceHolder.hpp
        ${INCROOT}/ResourceControl/ResourceLoader.hpp
        ${INCROOT}/ResourceControl/SFML_LoaderMakers.hpp

        ${INCROOT}/StateControl/State.hpp
        ${INCROOT}/StateControl/StateControl.hpp

        ${INCROOT}/States/MenuState.hpp

        ${INCROOT}/Structs/ConfigurationData.hpp

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
        #${SRCROOT}/ActionControl/Action.cpp

        ${SRCROOT}/Conversion/KeyConversion.cpp

        ${SRCROOT}/InputControl/AbstractDeviceController.cpp
        ${SRCROOT}/InputControl/EventBuffer.cpp
        ${SRCROOT}/InputControl/InputControl.cpp
        ${SRCROOT}/InputControl/KeyboardController.cpp
        ${SRCROOT}/InputControl/MouseController.cpp
        ${SRCROOT}/InputControl/WindowController.cpp

        ${SRCROOT}/StateControl/State.cpp
        ${SRCROOT}/StateControl/StateControl.cpp

        ${SRCROOT}/Structs/ConfigurationData.cpp

        ${SRCROOT}/States/MenuState.cpp

        ${SRCROOT}/Time/ApplicationClock.cpp
        ${SRCROOT}/Time/StopWatch.cpp

        ${SRCROOT}/Util/Logger.cpp

        ${SRCROOT}/Application.cpp
        ${SRCROOT}/main.cpp
   )

add_executable(${EXECUTABLE_NAME} ${FILES_HEADER} ${FILES_SRC})
target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBS})

