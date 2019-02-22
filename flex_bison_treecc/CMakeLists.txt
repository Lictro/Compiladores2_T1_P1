cmake_minimum_required (VERSION 2.6)
project (tarea)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++14")

# We use a custom lemon version
add_executable(lemon ${PROJECT_SOURCE_DIR}/tools/lemon.c)

# Run flex to generate the lexer
add_custom_command (
  OUTPUT lexer.cpp
  COMMAND flex -o lexer.cpp ${PROJECT_SOURCE_DIR}/lexer.l
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/lexer.l
  )
  
# Run lemon to generate the parser
add_custom_command (
  OUTPUT parser.cpp tokens.h
  COMMAND lemon -T${PROJECT_SOURCE_DIR}/tools/lempar.c -dtokens.h -oparser.cpp ${PROJECT_SOURCE_DIR}/parser.y
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/parser.y
  )

# Run treecc to generate the ast
add_custom_command (
  OUTPUT ast.h ast.cpp
  COMMAND treecc ${PROJECT_SOURCE_DIR}/ast.tc
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/ast.tc
  )

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
 
add_executable(${PROJECT_NAME} ast.cpp parser.cpp lexer.cpp main.cpp)

