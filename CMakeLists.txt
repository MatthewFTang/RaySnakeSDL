cmake_minimum_required(VERSION 3.31)
project(RaySnakeSDL)

set(CMAKE_CXX_STANDARD 23 )
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


find_package(SDL2 REQUIRED CONFIG REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
set(CMAKE_EXPORT_COMPILE_COMMANDS)

add_executable(${PROJECT_NAME} )
add_subdirectory(src)


target_link_libraries(${PROJECT_NAME}
        PRIVATE SDL2::SDL2
        SDL2_mixer::SDL2_mixer
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf)

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
