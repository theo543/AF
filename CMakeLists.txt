cmake_minimum_required(VERSION 3.20)
project(AF_HW)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -g")

include(CheckCXXSourceCompiles)
set(CMAKE_REQUIRED_FLAGS "-fsanitize=address,undefined")
check_cxx_source_compiles("#include <iostream>\nint main() { int arr[3] = {1, 2, 3}; int index; std::cin >> index; std::cout << arr[index]; return 0; }" SANITIZERS_SUPPORTED)
option(USE_SANITIZERS "Enable sanitizers if supported" ON)
if(USE_SANITIZERS AND SANITIZERS_SUPPORTED)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined")
    message(STATUS "Sanitizers enabled")
    add_compile_options(-fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
endif()

add_executable(test_bipart HW1/test_bipart.cpp)
add_executable(test_topsort HW1/test_topsort.cpp)
add_executable(test_safenodes HW1/test_safenodes.cpp)
add_executable(test_shortest_bridge HW1/test_shortest_bridge.cpp)
add_executable(test_shortest_bridge_optimized HW1/test_shortest_bridge_optimized.cpp)
add_executable(test_eqsat HW1/test_eqsat.cpp)
add_executable(directed_paths HW1/1144F_directed_paths.cpp)
add_executable(marked_nodes_diameter HW1/1881F_marked_nodes_diameter.cpp)
add_executable(padure HW1/padure.cpp)
add_custom_command(TARGET padure POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/HW1/padure.in ${CMAKE_CURRENT_BINARY_DIR}/padure.in
)
add_executable(test_critical_connections HW1/test_critical_connections.cpp)
add_executable(patrol2 HW1/patrol2.cpp)
add_executable(patrol2_optimized HW1/optimized/patrol2_optimized.cpp)
add_custom_command(TARGET patrol2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/HW1/patrol2.in ${CMAKE_CURRENT_BINARY_DIR}/patrol2.in
)
add_executable(padure_optimized HW1/optimized/padure_optimized.cpp)
add_executable(test_cheapest_flight_within_k_stops HW2/test_cheapest_flight_within_k_stops.cpp)
add_executable(test_checking_existence_limited_paths HW2/test_checking_existence_limited_paths.cpp)
add_executable(bile HW2/bile.cpp)
add_custom_command(TARGET bile POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/HW2/bile.in ${CMAKE_CURRENT_BINARY_DIR}/bile.in
)
add_executable(oracol HW2/oracol.cpp)
add_custom_command(TARGET oracol POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/HW2/oracol.in ${CMAKE_CURRENT_BINARY_DIR}/oracol.in
)
add_executable(apm2 HW2/apm2.cpp)
add_custom_command(TARGET apm2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/HW2/apm2.in ${CMAKE_CURRENT_BINARY_DIR}/apm2.in
)
add_executable(apm2_optimized HW2/apm2_optimized.cpp)
add_executable(dragoni HW2/dragoni.cpp)
add_custom_command(TARGET dragoni POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/HW2/dragoni.in ${CMAKE_CURRENT_BINARY_DIR}/dragoni.in
)
add_executable(camionase HW2/camionase.cpp)
add_custom_command(TARGET camionase POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/HW2/camionas.in ${CMAKE_CURRENT_BINARY_DIR}/camionase.in
)
add_executable(trilant HW2/trilant.cpp)
add_custom_command(TARGET trilant POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/HW2/trilant.in ${CMAKE_CURRENT_BINARY_DIR}/trilant.in
)
add_executable(test_find_critical_pseudo_critical HW2/test_find_critical_pseudo_critical.cpp)
add_executable(cablaj HW2/cablaj.cpp)
add_custom_command(TARGET cablaj POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/HW2/cablaj.in ${CMAKE_CURRENT_BINARY_DIR}/cablaj.in
)
add_executable(camionas_optimized HW2/camionas_optimized.cpp)
add_executable(dragoni_optimized HW2/dragoni_optimized.cpp)
add_executable(ghizi HW3/ghizi.cpp)
add_custom_command(TARGET ghizi POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/HW3/ghizi.in ${CMAKE_CURRENT_BINARY_DIR}/ghizi.in
)
add_executable(harta HW3/harta.cpp)
add_custom_command(TARGET harta POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/HW3/harta.in ${CMAKE_CURRENT_BINARY_DIR}/harta.in
)
add_executable(546E HW3/546E.cpp)
add_executable(negot HW3/negot.cpp)
add_custom_command(TARGET negot POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/HW3/negot.in ${CMAKE_CURRENT_BINARY_DIR}/negot.in
)
add_executable(paznici HW3/paznici.cpp)
add_custom_command(TARGET paznici POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/HW3/paznici.in ${CMAKE_CURRENT_BINARY_DIR}/paznici.in
)
add_executable(senat HW3/senat.cpp)
add_custom_command(TARGET senat POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/HW3/senat.in ${CMAKE_CURRENT_BINARY_DIR}/senat.in
)
add_executable(no_prime_sum HW3/no_prime_sum.cpp)
add_executable(test_shortest_path_all_nodes HW3/test_shortest_path_all_nodes.cpp)
add_executable(test_shortest_superstring HW3/test_shortest_superstring.cpp)
add_executable(test_reconstruct_itinerary HW3/test_reconstruct_itinerary.cpp)
add_executable(test_valid_arrangement_of_pairs HW3/test_valid_arrangement_of_pairs.cpp)
add_executable(cartite HW3/cartite.cpp)
add_custom_command(TARGET cartite POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/HW3/cartite.in ${CMAKE_CURRENT_BINARY_DIR}/cartite.in
)
add_executable(seg HW3/seg.cpp)
add_custom_command(TARGET seg POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/HW3/seg.in ${CMAKE_CURRENT_BINARY_DIR}/seg.in
)
add_executable(iepuri etc/iepuri.cpp)
add_custom_command(TARGET iepuri POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/etc/iepuri.in ${CMAKE_CURRENT_BINARY_DIR}/iepuri.in
)
