cmake_minimum_required(VERSION 3.20)

file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/**/*.cpp
)
file(GLOB_RECURSE GAME_HEADERS CONFIGURE_DEPENDS
    include/*.h
    include/**/*.h
)

add_executable(game
    ${GAME_SOURCES}
)

target_include_directories(game PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(game PRIVATE
    engine
)