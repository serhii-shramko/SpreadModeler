cmake_minimum_required(VERSION 3.16)

project(SpreadModelerTests)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED true)

file(GLOB HEADDIRS "../Headers/*")
list(APPEND HEADDIRS "../External/googletest/googletest/include")
include_directories(${HEADDIRS})

file(GLOB_RECURSE MAINSRCFILES "../Sources/*.cpp")
list(REMOVE_ITEM MAINSRCFILES ${CMAKE_SOURCE_DIR}/Tests/../Sources/main.cpp)
file(GLOB_RECURSE SRCFILES "*.cpp")
list(APPEND SRCFILES ${MAINSRCFILES})

add_executable(${PROJECT_NAME} ${SRCFILES})
target_link_libraries(${PROJECT_NAME} GTest::gtest_main)