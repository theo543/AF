cmake_minimum_required(VERSION 3.26)
project(AF_HW)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -g")
if(!WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined")
endif()

add_executable(test_bipart test_bipart.cpp)
add_executable(test_topsort test_topsort.cpp)
add_executable(test_safenodes test_safenodes.cpp)
