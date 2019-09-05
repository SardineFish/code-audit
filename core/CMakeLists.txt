cmake_minimum_required(VERSION 2.8)

project(libcode_audit_core)

#set(PROJECT_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})

file(GLOB SOURCES
    "${PROJECT_SOURCE_DIR}/include/**/*.h"
    "${PROJECT_SOURCE_DIR}/src/**/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/**/*.cc"
    "${PROJECT_SOURCE_DIR}/src/*.cc"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"

)
add_compile_options(-std=c++11)
add_compile_options(-g)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(code_audit_core SHARED ${SOURCES})
