set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE lib_sources "*.h" "*.cpp")

add_library(club_lib ${lib_sources})
add_executable(main ${lib_sources} main.cpp)