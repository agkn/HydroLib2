cmake_minimum_required(VERSION 3.10)
project(HydroLib2)
SET(CMAKE_COLOR_MAKEFILE OFF)
set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_FLAGS_DEBUG "-E")

add_subdirectory(lib)

add_executable(tests tests/testScript.cpp tests/testObjDaily.cpp)
target_link_libraries(tests  hydro2)

add_executable(main main.cpp )
target_link_libraries(main hydro2)

add_executable(script_test test.cpp)
target_link_libraries(script_test hydro2)
