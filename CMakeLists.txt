cmake_minimum_required(VERSION 3.15)
project(VoxelGL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(default_build_type "Debug")
    message(STATUS "Set the build type to `${default_build_type}` as none was specified.")
    set(CMAKE_BUILD_TYPE ${default_build_type} CACHE STRING "Choose the build type." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
message(STATUS "${PROJECT_NAME} Build Type: ${CMAKE_BUILD_TYPE}")

set(Version_Major 0)
set(Version_Minor 0)
set(PROJECT_VERSION
    "${Version_Major}.${Version_Minor}"
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

if(NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "Windows") # If linux, try finding all the libraries. If couldn't find them, compile from scratch.
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
else()
    set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/external/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${PROJECT_SOURCE_DIR}/external/glm)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
