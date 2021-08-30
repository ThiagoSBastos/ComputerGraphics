cmake_minimum_required(VERSION 3.0.0)
project(assigment2 VERSION 0.1.0)

cmake_policy(SET CMP0042 NEW)

# prefer OpenGL libraries from a hardware vendor if available
set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(FreeGLUT REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17 -lGL -lglut -lGLU")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g -std=c++17 -lGL -lglut -lGLU")
include_directories(library ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

include(CTest)
enable_testing()

add_executable(assigment2 main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)