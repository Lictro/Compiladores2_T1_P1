cmake_minimum_required (VERSION 2.6)
project (tarea2)

set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++14" )

# Run flex to generate the lexer
add_custom_command (
  OUTPUT lexer.h
  COMMAND flex -o lexer.h ${PROJECT_SOURCE_DIR}/../tarea2.l
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/../tarea2.l
  )

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../)
  
add_executable(${PROJECT_NAME} 
                lexer.h
                main.cpp)

enable_testing()
add_test(NAME ${PROJECT_NAME}
         COMMAND ${PROJECT_NAME})
