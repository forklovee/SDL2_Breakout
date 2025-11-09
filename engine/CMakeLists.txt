cmake_minimum_required(VERSION 3.20)

add_library(engine STATIC)

target_sources(engine PRIVATE
    src/core/game.cpp
    src/core/window.cpp
    src/core/timing.cpp
    src/core/input.cpp

    src/graphics/object2d.cpp
    src/graphics/image/image.cpp
    src/graphics/image/animated_image.cpp
    src/graphics/image/text_image.cpp
    src/ui/button/button.cpp

    src/entity/ball_entity.cpp
    src/entity/paddle_entity.cpp
)

target_include_directories(engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_link_libraries(engine
    PUBLIC
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
)
