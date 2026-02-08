cmake_minimum_required (VERSION 3.31)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    arieo_engine_project(
        arieo_x11_window_module
        ALIAS arieo::modules::window::x11
        PROJECT_TYPE module
        SOURCES
            ${CMAKE_CURRENT_SOURCE_DIR}/private/src/*.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/private/src/*/*.cpp
        INTERFACES
            arieo::interface::window
        LIBS
            arieo::base
            arieo::core
            x11
    )
endif()