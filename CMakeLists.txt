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
add_executable(test_shortest_bridge test_shortest_bridge.cpp)
add_executable(test_shortest_bridge_optimized test_shortest_bridge_optimized.cpp)
add_executable(test_eqsat test_eqsat.cpp)
add_executable(directed_paths 1144F_directed_paths.cpp)
add_executable(marked_nodes_diameter 1881F_marked_nodes_diameter.cpp)
add_executable(padure padure.cpp)
add_custom_command(TARGET padure POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/padure.in ${CMAKE_CURRENT_BINARY_DIR}/padure.in
)
add_executable(test_critical_connections test_critical_connections.cpp)
add_executable(patrol2 patrol2.cpp)
add_executable(patrol2_optimized patrol2_optimized.cpp)
add_custom_command(TARGET patrol2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/patrol2.in ${CMAKE_CURRENT_BINARY_DIR}/patrol2.in
)
add_executable(padure_optimized padure_optimized.cpp)
