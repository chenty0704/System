cmake_minimum_required(VERSION 3.27)

project(System
        VERSION 1.0
        DESCRIPTION "Core functionalities for C++"
        LANGUAGES CXX)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

set(Boost_NO_WARN_NEW_VERSIONS ON)

find_package(Boost REQUIRED COMPONENTS json)
find_package(mdspan REQUIRED CONFIG)

include_directories(Headers)

add_subdirectory(Headers)
add_subdirectory(Tests)

install(FILES cmake/SystemConfig.cmake
        DESTINATION share/System)
