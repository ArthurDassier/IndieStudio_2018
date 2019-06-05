LINK_DIRECTORIES (
    ../../Bomberman/lib
)

project(server_tests)

add_executable(
    server_tests
    tests_server.cpp
    tests_room.cpp
    tests_participant.cpp
)

set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-lgcov")

# add_custom_target(module_tmp_tests COMMAND "-coverage")
# target_compile_options²(module_tmp_tests INTERFACE --coverage)
# set(CMAKE_CXX_OUTPUT_ENTENSION_REPLACE ON)
# set(CMAKE_EXE_LINKER "-fprofile-arcs -ftest-coverage")

set_target_properties(server_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

target_link_libraries(
    server_tests
    gtest
    gtest_main
    server
    boost_system
    boost_timer
    pthread
)
