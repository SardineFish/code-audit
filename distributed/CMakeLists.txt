cmake_minimum_required(VERSION 2.8)

project(code_audit_distributed)

#set(PROJECT_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})

include_directories("${CMAKE_SOURCE_DIR}/../core/include")
include_directories("${CMAKE_SOURCE_DIR}/include")

add_subdirectory("${CMAKE_SOURCE_DIR}/../core" "${CMAKE_SOURCE_DIR}/../core/build/lib_build")

add_compile_options(-std=c++11)
add_compile_options(-g)

file(GLOB SOURCES
    "${PROJECT_SOURCE_DIR}/include/**/*.h"
    "${PROJECT_SOURCE_DIR}/src/lib/**/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/lib/**/*.cc"
    "${PROJECT_SOURCE_DIR}/src/lib/*.cc"
    "${PROJECT_SOURCE_DIR}/src/lib/*.cpp"

)

add_library(code_audit_distributed SHARED ${SOURCES})

add_executable(dist_node src/node/node.cpp)
add_executable(dist_master src/master/test.cpp)

target_link_libraries(code_audit_distributed code_audit_core)
target_link_libraries(code_audit_distributed pthread)
target_link_libraries(dist_node code_audit_core code_audit_distributed)
target_link_libraries(dist_master code_audit_core code_audit_distributed)