set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../include/${CMAKE_PROJECT_NAME})
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR})

# Files
set(FILES_HEADER
        #
   )

set(FILES_SRC
        ${SRCROOT}/main.cpp
   )

add_executable(${EXECUTABLE_NAME} ${FILES_HEADER} ${FILES_SRC})
target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBS})

