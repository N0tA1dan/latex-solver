cmake_minimum_required (VERSION 3.5)

project (latex-solver CXX)


add_executable(
  solver
  src/main.cpp
  src/lexer.cpp
  src/parser.cpp
)

target_include_directories(solver PRIVATE include)
