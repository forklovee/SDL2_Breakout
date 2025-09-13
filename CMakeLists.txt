cmake_minimum_required(VERSION 3.16)
project(Breakout)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

#SDL2_INCLUDE_DIRS is a SDL2 constant it seems...
include_directories(${SDL2_INCLUDE_DIRS} include)

file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})