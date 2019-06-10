project(server_tests)

LINK_DIRECTORIES (
    ../../lib
)

include_directories(
    ../include
    ../../lib/include
)

add_executable(
    server_tests
    tests_server.cpp
    tests_room.cpp
)

set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-lgcov")
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -no-pie")

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
