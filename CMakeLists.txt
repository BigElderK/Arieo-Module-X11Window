cmake_minimum_required (VERSION 3.31)

include($ENV{ARIEO_BUILD_ENV_PACKAGES_OUTPUT_DIR}/cmake/build_environment.cmake)

ARIEO_PACKAGE(
    Arieo-Module-X11Window
    CATEGORY 02_engine
    DEPENDS
        https://github.com/BigElderK/Arieo-Core.git@main
        https://github.com/BigElderK/Arieo-Interface-Window.git@main
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    ARIEO_ENGINE_PROJECT(
        arieo_x11_window_module
        PROJECT_TYPE module

        DEPENDENCIES
            ARIEO_PACKAGES
                Arieo-Core
                Arieo-Interface-Window
            PRIVATE_LIBS
                Arieo-Interface-Window::arieo_window_interface
                Arieo-Core::arieo_core
                x11

        SOURCES
            CXX_SOURCES
                ${CMAKE_CURRENT_LIST_DIR}/private/src/*.cpp
                ${CMAKE_CURRENT_LIST_DIR}/private/src/*/*.cpp
    )
else()
    # Create a dummy install target for non-Linux platforms
    message(STATUS "Arieo-Module-X11Window: Skipping build for ${CMAKE_SYSTEM_NAME} (Linux only)")
    install(CODE "message(STATUS \"Arieo-Module-X11Window: No installation needed for ${CMAKE_SYSTEM_NAME}\")")
endif()
