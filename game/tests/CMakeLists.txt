LINK_DIRECTORIES (
    ../../Bomberman/lib
)

project(game_tests)

add_executable(
    game_tests
    tests_character.cpp
)
set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -no-pie")
set(CMAKE_EXE_LINKER_FLAGS "-lgcov")

# add_custom_target(module_tmp_tests COMMAND "-coverage")
# target_compile_options²(module_tmp_tests INTERFACE --coverage)
# set(CMAKE_CXX_OUTPUT_ENTENSION_REPLACE ON)
# set(CMAKE_EXE_LINKER "-fprofile-arcs -ftest-coverage")

set_target_properties(client_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

target_link_libraries(
    game_tests
    gtest
    gtest_main
    game
    boost_system
    boost_timer
    pthread
    Irrlicht
    GL
    Xxf86vm
    Xext
    X11
    Xcursor
)
