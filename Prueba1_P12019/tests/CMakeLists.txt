cmake_minimum_required (VERSION 2.6)
project (test_lexer)

set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++14" )

# Run flex to generate the lexer
add_custom_command (
  OUTPUT lexer.cpp
  COMMAND flex -o lexer.cpp ${PROJECT_SOURCE_DIR}/../lexer.l
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/../lexer.l
  )

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../)
  
add_executable(${PROJECT_NAME} 
                lexer.cpp
                test_lexer.cpp)

enable_testing()
add_test(NAME ${PROJECT_NAME}
         COMMAND ${PROJECT_NAME})
