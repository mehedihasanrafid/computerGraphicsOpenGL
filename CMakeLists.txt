cmake_minimum_required(VERSION 3.16)

project(
    OpenGLYachtJourney
    VERSION 2.1.0
    DESCRIPTION "Interactive multi-scene 2D yacht animation using C++ and OpenGL/GLUT"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(yacht_journey
    src/main.cpp
    src/App.cpp
    src/Audio.cpp
    src/GraphicsPrimitives.cpp
    src/Scene.cpp
    src/Yacht.cpp
    src/scenes/BeachScene.cpp
    src/scenes/MountainsScene.cpp
    src/scenes/CityScene.cpp
    src/scenes/HarborScene.cpp
)

target_include_directories(yacht_journey PRIVATE include)

target_link_libraries(yacht_journey
    PRIVATE
        OpenGL::GL
        GLUT::GLUT
)

if(WIN32)
    target_compile_definitions(yacht_journey PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
    target_link_libraries(yacht_journey PRIVATE winmm gdi32)
endif()

if(MSVC)
    target_compile_options(yacht_journey PRIVATE /W4 /permissive-)
else()
    target_compile_options(yacht_journey PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()

install(TARGETS yacht_journey RUNTIME DESTINATION bin)
