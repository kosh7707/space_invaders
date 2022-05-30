cmake_minimum_required(VERSION 3.17)
project(space_invaders)

set(CMAKE_CXX_STANDARD 17)

# Windows specific config
IF (WIN32)
    # Include local sfml cmake config
    set(SFML_DIR "C:/SFML/lib/cmake/SFML")
    # Link sfml statically (Optional)
    set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)

FILE(
        GLOB
        SOURCES
        "*.h"
        "*.cpp"
)

add_executable(space_invaders ${SOURCES} GameObject.cpp InputHandler.cpp VolumeControl.h)

target_link_libraries(space_invaders sfml-graphics sfml-audio)

target_include_directories(space_invaders
        PRIVATE
        "${PROJECT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        )

file(COPY graphics sound fonts world DESTINATION ${CMAKE_BINARY_DIR})