cmake_minimum_required(VERSION 3.10)
project(fluxcpp)

set(CMAKE_CXX_STANDARD 20)

set(CPP_FILES 
    src/flux.cc
    src/session.cc
)

set(HEADER_FILES,
    include/session.h
)

add_executable(fluxcpp ${CPP_FILES} ${HEADER_FILES})
target_include_directories(fluxcpp PRIVATE include/)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG a2d35a1cb9f3f7e2f1469d6a189751331dc99f96) 
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)

FetchContent_MakeAvailable(json)
FetchContent_MakeAvailable(cpr)

target_link_libraries(fluxcpp PRIVATE cpr::cpr)
target_link_libraries(fluxcpp PRIVATE nlohmann_json::nlohmann_json)
