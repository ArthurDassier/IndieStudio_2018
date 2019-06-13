project(client_tests)

LINK_DIRECTORIES (
    ../../lib
)

INCLUDE_DIRECTORIES (
    ../../lib/include
)

add_executable(
    client_tests
    tests_clock.cpp
)

set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -no-pie")

set_target_properties(client_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

if (WIN32)
    target_link_libraries(
        client_tests
        client
        gtest
        gtest_main
        Irrlicht
    )
else ()
    set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "-lgcov")
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
endif ()
