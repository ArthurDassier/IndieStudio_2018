project(client_tests)

LINK_DIRECTORIES (
    ../../lib
)

include_directories(
    ../../lib/include
    ../include
)

add_executable(
    client_tests
    tests_clock.cpp
)

set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -no-pie")
set(CMAKE_EXE_LINKER_FLAGS "-lgcov")

set_target_properties(client_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

target_link_libraries(
    client_tests
    gtest
    gtest_main
    client
    boost_system
    boost_timer
    pthread
    Irrlicht
    GL
    Xxf86vm
    X11
)
