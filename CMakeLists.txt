cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_REQUIRED ON)

project(littlecraftGL)

file(GLOB_RECURSE SRC_FILES src/*.c*)
file(GLOB_RECURSE SHADERS_FILES shaders/*)
file(GLOB_RECURSE RES_FILES res/*)

file(COPY ${SHADERS_FILES} DESTINATION ${CMAKE_BINARY_DIR}/shaders)
file(COPY ${RES_FILES} DESTINATION ${CMAKE_BINARY_DIR}/res)

find_package(OpenGL REQUIRED)

add_executable(littlecraftGL ${SRC_FILES})

if(WIN32)
    # set stuff for windows
    target_include_directories(littlecraftGL
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui
        ${USERPROFILE}/glfw/include
        ${USERPROFILE}/glm
        ${USERPROFILE}/stb)

    target_link_libraries(littlecraftGL
        PUBLIC
        opengl32
        glfw3
        pthread)

else()
    target_include_directories(littlecraftGL
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui
        ${OPENGL_INCLUDE_DIR})

    target_link_libraries(littlecraftGL
        PUBLIC
        GL
        glfw
        pthread)
endif()