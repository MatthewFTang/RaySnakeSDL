cmake_minimum_required(VERSION 3.28)
project(RaySnakeSDL)

set(CMAKE_CXX_STANDARD 23)
find_package(SDL2 REQUIRED CONFIG REQUIRED)

find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Core/Application.h
        src/Core/Application.cpp
        src/Core/Game.h
        src/Menu/Menu.h
        src/Menu/MainMenu.h
        src/Objects/Food.h
        src/Objects/Player.h
        src/Objects/Player.cpp
        src/Objects/GameObject.cpp
        src/Objects/Food.cpp
        src/Core/LoaderParams.h
        src/Managers/FontManger.cpp
        src/Managers/SoundManger.cpp
        src/Managers/TextureManger.cpp
        src/Core/Vector2.cpp
        src/Core/Vector2.h
        src/Managers/InputManager.cpp
        src/Managers/InputManager.h
        src/Core/Game.cpp
        src/Menu/MainMenu.cpp
        src/Menu/DifficultlyMenu.cpp
        src/Core/Level.cpp
        src/Menu/AboutMenu.cpp)

include_directories(src)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2_mixer::SDL2_mixer SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf)
# Specify the source directory containing your resources
set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/src/resources")

# Specify the destination directory in the build folder
set(DEST_DIR "${CMAKE_BINARY_DIR}/src/")

# Copy the directory
file(COPY ${RESOURCE_DIR} DESTINATION ${DEST_DIR})

