set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../include/${CMAKE_PROJECT_NAME})
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR})

# Files
set(FILES_HEADER
        ${INCROOT}/StateControl/State.hpp
        ${INCROOT}/StateControl/StateControl.hpp
        ${INCROOT}/StateControl/StateIdentifiers.hpp

        ${INCROOT}/Util/Logger.hpp
        ${INCROOT}/Util/ThrowAssert.hpp
        ${INCROOT}/Util/Util.hpp

        ${INCROOT}/Application.hpp
        ${INCROOT}/defines.hpp
        ${INCROOT}/GlobalColours.hpp
   )

set(FILES_SRC
        ${SRCROOT}/StateControl/StateControl.cpp

        ${SRCROOT}/Util/Logger.cpp

        ${SRCROOT}/Application.cpp
        ${SRCROOT}/main.cpp
   )

add_executable(${EXECUTABLE_NAME} ${FILES_HEADER} ${FILES_SRC})
target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBS})

