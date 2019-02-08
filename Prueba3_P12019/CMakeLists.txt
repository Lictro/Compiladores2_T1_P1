cmake_minimum_required (VERSION 2.6)
project (EasyASM)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++14")

# Run flex to generate the lexer
add_custom_command (
  OUTPUT expr_lexer.cpp
  COMMAND flex -o expr_lexer.cpp ${PROJECT_SOURCE_DIR}/expr.l
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/expr.l
  )
  
# Run bison to generate the parser
add_custom_command (
  OUTPUT expr_parser.cpp expr_tokens.h
  COMMAND bison -o expr_parser.cpp -rall --defines=expr_tokens.h ${PROJECT_SOURCE_DIR}/expr.y
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/expr.y
  )

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
 
add_executable(expr expr_parser.cpp expr_lexer.cpp ast.cpp main.cpp)

