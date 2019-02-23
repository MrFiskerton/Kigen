cmake_minimum_required(VERSION 3.11.4)
message(STATUS "Start running CMake...")

# Project name
project(Yosai)

# Setup version numbers
set( VERSION_MAJOR 0 )
set( VERSION_MINOR 0 )
set( VERSION_PATCH 1 )

set(EXECUTABLE_NAME ${PROJECT_NAME})
set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#----------------------------------------------------------------------------------------------------------------#
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

# Custom compiler flags
set(WARNING "-Wall -Wextra -Wshadow -Wnon-virtual-dtor ") # -Werror -Weffc++ -pedantic
set(FLAGS "-std=c++1y -O3 -s ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNING} ${FLAGS}")

#Set output dirs
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIB_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build_final)

#----------------------------------------------------------------------------------------------------------------#
set(SFML_DIR "${PROJECT_ROOT_DIR}/deps/SFML")
set(JSON_DIR "${PROJECT_ROOT_DIR}/deps/JSON")

include_directories("${SFML_DIR}/include/" ${JSON_DIR})
set(SFML_LIBRARIES sfml-graphics sfml-window sfml-system sfml-audio)
set(LIBS ${SFML_LIBRARIES})

#----------------------------------------------------------------------------------------------------------------#
if(UNIX)
    add_definitions(-DYOSAI_LINUX)
elseif(WIN32)
    add_definitions(-DYOSAI_WINDOWS)
endif()

#----------------------------------------------------------------------------------------------------------------#
# C++ source code, list of all subdirectories

# Add the header path
include_directories(${PROJECT_ROOT_DIR}/include)

# Add the subdirectories
add_subdirectory(${PROJECT_ROOT_DIR}/src/${CMAKE_PROJECT_NAME})
add_subdirectory(${PROJECT_ROOT_DIR}/src/Kigen) ####
#----------------------------------------------------------------------------------------------------------------#
