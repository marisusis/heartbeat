cmake_minimum_required(VERSION 3.18)
project(heartbeat)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

include(cmake/raylib.cmake)
include(cmake/fmt.cmake)

file(GLOB_RECURSE HB_SOURCES_CPP "lib/hb/*.cpp")
file(GLOB_RECURSE HB_SOURCES_C "lib/hb/*.c")
add_library(libheartbeat SHARED ${HB_SOURCES_CPP} ${HB_SOURCES_C})
target_include_directories(libheartbeat PUBLIC "lib/hb")

add_executable(${PROJECT_NAME} "src/main.cpp")

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib fmt::fmt)
target_include_directories(${PROJECT_NAME} PRIVATE external/raylib)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

add_executable(hb-convert "tools/hb-convert.c")
target_link_libraries(hb-convert libheartbeat)