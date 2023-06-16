cmake_minimum_required(VERSION 3.16)

project(SpreadModeler)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED true)

add_subdirectory("./External/googletest")
add_subdirectory("./Tests")

file(GLOB HEADDIRS "./Headers/*")
include_directories(${HEADDIRS})

file(GLOB_RECURSE SRCFILES "./Sources/*.cpp")
add_executable(${PROJECT_NAME} ${SRCFILES} ${PRECOMPILED_HEADER_FILE})

set(PRECOMPILED_HEADER_FILE "./Headers/pch/pch.hpp")
target_precompile_headers(${PROJECT_NAME} PRIVATE ${PRECOMPILED_HEADER_FILE})