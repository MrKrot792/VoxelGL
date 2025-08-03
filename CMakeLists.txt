cmake_minimum_required(VERSION 3.15)
project(VoxelGL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(default_build_type "Debug")
    message(STATUS "Set the build type to `${default_build_type}` as none was specified.")
    set(CMAKE_BUILD_TYPE ${default_build_type} CACHE STRING "Chooce the build type." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
message(STATUS "${PROJECT_NAME} Build Type: ${CMAKE_BUILD_TYPE}")

set(Version_Major 0)
set(Version_Minor 0)
set(PROJECT_VERSION
    "${myProject_Version_Major}.${myProject_Version_Minor}"
)
message(STATUS "${PROJECT_NAME} version: ${PROJECT_VERSION}")

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/lib)

file(GLOB_RECURSE SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.c
    ${PROJECT_SOURCE_DIR}/lib/*.cpp
    ${PROJECT_SOURCE_DIR}/lib/*.c
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

find_package(glfw3)
if(glfw3_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
else()
    message("Could not find glfw, fallback to subproject")
    add_subdirectory(${PROJECT_SOURCE_DIR}/external/glfw/)
endif()

find_package(glm)
if(glm_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE glm)
else()
    message("Could not find glm, fallback to subproject")
    add_subdirectory(${PROJECT_SOURCE_DIR}/external/glm)
endif()

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glfw glm)
