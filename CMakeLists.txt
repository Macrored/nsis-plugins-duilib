cmake_minimum_required (VERSION 2.8)

add_definitions(-std=c++11)
add_definitions(-DUNICODE -D_UNICODE)

project(NsisPluginsDemo)

set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")

add_subdirectory(DuiLib)
add_subdirectory(360SafeDemo)
add_subdirectory(NsisPlugin)
