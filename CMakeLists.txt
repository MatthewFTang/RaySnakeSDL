cmake_minimum_required(VERSION 3.8)
project(RaySnakeSDL)

set(CMAKE_CXX_STANDARD 20 )
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
set(CMAKE_EXPORT_COMPILE_COMMANDS)
target_link_libraries(${PROJECT_NAME}
        PRIVATE SDL2::SDL2
        SDL2_mixer::SDL2_mixer
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf)
# Specify the source directory containing your resources
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
# Define the source directory for the resources
set(RESOURCES_FOLDER "${CMAKE_SOURCE_DIR}/src/resources")

# Define the directory to copy resources to (inside the build directory)
set(RESOURCES_OUTPUT_FOLDER "${CMAKE_BINARY_DIR}/src/resources")

# Verify that the source `resources` folder exists before copying
if(EXISTS ${RESOURCES_FOLDER})
    add_custom_target(CopyResources ALL
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${RESOURCES_FOLDER}" "${RESOURCES_OUTPUT_FOLDER}"
            COMMENT "Copying resources to build directory"
    )

    # Ensure resources are copied before building the executable
    add_dependencies(${PROJECT_NAME} CopyResources)
else()
    message(FATAL_ERROR "The resources folder does not exist at ${RESOURCES_FOLDER}")
endif()
