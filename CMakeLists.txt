cmake_minimum_required(VERSION 3.8)

project(SpreadModeler)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_COMPILER "g++")

file(GLOB HEADDIRS "./Headers/*")
include_directories(${HEADDIRS})

file(GLOB_RECURSE SRCFILES "./Sources/*.cpp")
add_executable(${PROJECT_NAME} ${SRCFILES})