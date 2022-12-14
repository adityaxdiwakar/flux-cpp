cmake_minimum_required(VERSION 3.10)
project(fluxcpp)

set(CPP_FILES "${PROJECT_SOURCE_DIR}/src/flux.cc")

add_executable(fluxcpp ${CPP_FILES})

