cmake_minimum_required (VERSION 3.31)

include($ENV{ARIEO_BUILDENV_PACKAGE_INSTALL_FOLDER}/cmake/build_environment.cmake)
project(ArieoEngine)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    arieo_engine_project(
        arieo_x11_window_module
        PROJECT_TYPE module

        PACKAGES
            Arieo-Interface-Window
            Arieo-Core
        INTERFACES
            Arieo-Interface-Window::arieo_window_interface
        PRIVATE_LIBS
            Arieo-Core::arieo_core
            x11
        
        SOURCES
            ${CMAKE_CURRENT_SOURCE_DIR}/private/src/*.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/private/src/*/*.cpp
    )
endif()