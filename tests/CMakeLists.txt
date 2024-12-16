set(BINARY ${CMAKE_PROJECT_NAME}_test)

enable_testing()

file(GLOB_RECURSE test_sources "*.h*" "*.cpp*")
add_executable(${BINARY} ${test_sources})
target_include_directories(${BINARY} PRIVATE ${CMAKE_SOURCE_DIR}/src)
add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PRIVATE gtest gmock club_lib)