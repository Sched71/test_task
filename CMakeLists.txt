cmake_minimum_required (VERSION 3.10)
project (club)
set(CMAKE_CXX_STANDARD 20)
set(RELEASE_BUILD_OPTS "-O3")
set(DEBUG_BUILD_OPTS "-O0"
    "-g"
    "-Wall"
    "-Wextra"
    "-Werror"
    "-fno-omit-frame-pointer"
    "-fno-optimize-sibling-calls")

add_compile_options("$<$<CONFIG:Debug>:${DEBUG_BUILD_OPTS}>")
add_compile_options("$<$<CONFIG:Release>:${RELEASE_BUILD_OPTS}>")   

add_subdirectory("googletest")
add_subdirectory("tests")
add_subdirectory("src")
