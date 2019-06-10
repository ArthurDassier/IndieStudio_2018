project(game_tests)

LINK_DIRECTORIES (
    ../../lib
)

include_directories(
    ../include
)

add_executable(
    game_tests
    tests_character.cpp
)

set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -no-pie")
set(CMAKE_EXE_LINKER_FLAGS "-lgcov")

target_link_libraries(
    game_tests
    gtest
    gtest_main
    game
    pthread
)

set_target_properties(game_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
