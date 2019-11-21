cmake_minimum_required(VERSION 2.8)

project(code_audit_test)

#set(PROJECT_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})

include_directories("${CMAKE_SOURCE_DIR}/../core/include")

add_subdirectory("${CMAKE_SOURCE_DIR}/../core" "${CMAKE_SOURCE_DIR}/../core/build/test_build")

add_compile_options(-std=c++11)
add_compile_options(-g)
add_compile_options(-pthread)
add_executable(test src/test.cpp)
add_executable(test_lexer src/lexer/test_lexer.cpp)
add_executable(test_parser src/test_parser.cpp)
add_executable(diff_tree src/tree_diff.cpp)
add_executable(ast_diff src/ast_diff.cpp)
add_executable(syntax_test src/parser/syntax_test.cpp)
add_executable(audit_test src/test_audit.cpp)
add_executable(channel_test src/test_channel.cpp)
add_executable(ast_test src/parser/ast_test.cpp)

target_link_libraries(test code_audit_core)
target_link_libraries(test_lexer code_audit_core)
target_link_libraries(test_parser code_audit_core)
target_link_libraries(diff_tree code_audit_core)
target_link_libraries(ast_diff code_audit_core)
target_link_libraries(syntax_test code_audit_core)
target_link_libraries(audit_test code_audit_core)
target_link_libraries(channel_test code_audit_core)
target_link_libraries(channel_test pthread)
target_link_libraries(ast_test code_audit_core)