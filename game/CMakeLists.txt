cmake_minimum_required(VERSION 3.20)

add_executable(game)

target_sources(game PRIVATE
    src/main.cpp
    # src/entity/ball_entity.cpp
)

target_include_directories(game 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include

)

target_link_libraries(game 
    PRIVATE
        engine
)