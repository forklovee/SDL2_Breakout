cmake_minimum_required(VERSION 3.16)
project(Breakout)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/SDL2
    )

if (WIN32)
    message(STATUS "Configuring for Windows!")
    link_directories(
        ${CMAKE_SOURCE_DIR}/external/SDL2
        ${CMAKE_SOURCE_DIR}/external/SDL2_image
        )
    
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-mwindows")

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/bin/SDL2.dll
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/bin/SDL2_image.dll
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )

elseif (UNIX)
    message(STATUS "Configuring for Linux!")
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)

endif()

file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image)

