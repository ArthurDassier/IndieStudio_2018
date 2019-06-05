project(client_tests)

add_executable(
    client_tests
    tests_clock.cpp
)

set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-lgcov")

# add_custom_target(module_tmp_tests COMMAND "-coverage")
# target_compile_options²(module_tmp_tests INTERFACE --coverage)
# set(CMAKE_CXX_OUTPUT_ENTENSION_REPLACE ON)
# set(CMAKE_EXE_LINKER "-fprofile-arcs -ftest-coverage")

set_target_properties(client_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

target_link_libraries(
    client_tests
    gtest
    gtest_main
    client
    boost_system
    pthread
    module_tmp
    boost_timer
)
