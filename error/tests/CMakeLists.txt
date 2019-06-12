project(error_tests)

LINK_DIRECTORIES (
    ../../lib
)

include_directories(
    ../../lib/include
)

add_executable(
    error_tests
    tests_error.cpp
)

set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-lgcov")
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -no-pie")

set_target_properties(error_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

target_link_libraries(
    error_tests
    gtest
    gtest_main
    error
    pthread
)
