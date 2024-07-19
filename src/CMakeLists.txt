# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.


project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD)
file(GLOB_RECURSE SOURCE_FILE CONFIGURE_DEPENDS *.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILE})

