cmake_minimum_required (VERSION 2.6)
project (test_parser)

set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++14" )

# Run treec to generate the AST
add_custom_command (
  OUTPUT expr_ast.cpp expr_ast.h
  COMMAND treecc -o expr_ast.cpp -h expr_ast.h ${PROJECT_SOURCE_DIR}/../expr_ast.tc
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/../expr_ast.tc
  )

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../)
  
add_executable(test_ast expr_ast.cpp
                        test_ast.cpp)

enable_testing()
add_test(NAME test_ast
         COMMAND test_ast)
