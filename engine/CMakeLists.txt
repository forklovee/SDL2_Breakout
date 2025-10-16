cmake_minimum_required(VERSION 3.20)

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/**/*.cpp
)
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    include/*.h
    include/**/*.h
)

add_library(engine STATIC)

target_sources(engine PRIVATE
    src/core/game.cpp
    src/graphics/image/image.cpp
)

target_include_directories(engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

target_link_libraries(engine
    PUBLIC
        SDL2::SDL2
        SDL2_image::SDL2_image
)