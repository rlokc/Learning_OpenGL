cmake_minimum_required(VERSION 2.8)

project(OpenGL_Transformations)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

find_package(OpenGL REQUIRED)
include_directories(include ${GLFW_INCLUDE_DIRS})
set(HEADER_FILES include/glad/glad.h include/KHR/khrplatform.h include/shader.h include/stb_image.h)

add_executable(${PROJECT_NAME} src/main.cpp src/glad.c src/shader.cpp ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARY} ${GLFW_LIBRARIES} dl)
