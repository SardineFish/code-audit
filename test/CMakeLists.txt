cmake_minimum_required(VERSION 2.8)

project(code_audit_test)

#set(PROJECT_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})

include_directories("${CMAKE_SOURCE_DIR}/../core/include")

add_subdirectory("${CMAKE_SOURCE_DIR}/../core" "${CMAKE_SOURCE_DIR}/../core/build/test_build")

add_compile_options(-std=c++11)
add_compile_options(-g)

add_executable(test src/test.cpp)

add_executable(test_lexer src/lexer/test_lexer.cpp)

target_link_libraries(test code_audit_core)
target_link_libraries(test_lexer code_audit_core)