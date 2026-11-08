# Sudoku Solver
# CopyRight (C) 2026, Enrico P. Metzner

cmake_minimum_required(VERSION 3.18)

cmake_policy(SET CMP0076 NEW)
include(FetchContent)

project(FraktalZoom
    VERSION 0.0.1
    DESCRIPTION "Fraktal Zoom explorer"
    LANGUAGES CXX)

add_executable(${PROJECT_NAME})

# list(APPEND CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_FULL_LIBDIR})
# set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(CMAKE_BUILD_TYPE Release)

find_package(OpenGL REQUIRED)

if(NOT OpenGL_OpenGL_FOUND)
  message(FATAL_ERROR "OpenGL::OpenGL not found but required!")
endif()

FetchContent_Declare(
  glew
  # hint from https://stackoverflow.com/questions/73575450/modern-cmake-way-to-add-glew-and-other-opengl-stuff
  GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
  GIT_TAG        glew-cmake-2.3.1
)
FetchContent_MakeAvailable(glew)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.5.1
)
FetchContent_MakeAvailable(glfw)

#FetchContent_Declare(
#  yaml-cpp
#  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
#  GIT_TAG        yaml-cpp-0.9.0 # Can be a tag (yaml-cpp-x.x.x), a commit hash, or a branch name (master)
#)
#FetchContent_MakeAvailable(yaml-cpp)

FetchContent_Declare(
  json
  URL                        https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(json)

# add_subdirectory(src/helpers)
add_subdirectory(src/gfx)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    #yaml-cpp::yaml-cpp
    nlohmann_json::nlohmann_json
    ${OPENGL_LIBRARIES}
  PUBLIC
    libglew_static
    glfw
)

target_sources(${PROJECT_NAME}
    PRIVATE
        src/AppMain.h
        src/AppMain.cpp
)
