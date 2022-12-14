cmake_minimum_required(VERSION 3.10)
project(fluxcpp)

set(CMAKE_CXX_STANDARD 20)

set(CPP_FILES "${PROJECT_SOURCE_DIR}/src/flux.cc")

add_executable(fluxcpp ${CPP_FILES})

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG a2d35a1cb9f3f7e2f1469d6a189751331dc99f96) 
FetchContent_MakeAvailable(cpr)

target_link_libraries(fluxcpp PRIVATE cpr::cpr)
