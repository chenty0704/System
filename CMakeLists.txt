cmake_minimum_required(VERSION 3.27)

project(System
        VERSION 1.0
        DESCRIPTION "Core utilities for C++"
        HOMEPAGE_URL "https://github.com/chenty0704/System"
        LANGUAGES CXX)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

set(Boost_NO_WARN_NEW_VERSIONS ON)

find_package(Boost REQUIRED COMPONENTS json)
find_package(GTest REQUIRED CONFIG)
find_package(mdspan REQUIRED CONFIG)

include_directories(include)

add_subdirectory(include)
add_subdirectory(tests)

install(FILES
        cmake/SystemConfig.cmake
        System.natvis
        DESTINATION share/System)
