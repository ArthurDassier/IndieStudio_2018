LINK_DIRECTORIES (
    ../../Bomberman/lib
)

project(utils_tests)

add_executable(
    utils_tests
    tests_character.cpp
)

set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -no-pie")

# add_custom_target(module_tmp_tests COMMAND "-coverage")
# target_compile_options²(module_tmp_tests INTERFACE --coverage)
# set(CMAKE_CXX_OUTPUT_ENTENSION_REPLACE ON)
# set(CMAKE_EXE_LINKER "-fprofile-arcs -ftest-coverage")

set_target_properties(client_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

if (WIN32)
    target_link_libraries(
        utils_tests
        gtest
        gtest_main
        game
        Irrlicht
    )
else ()
    set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "-lgcov")

    target_link_libraries(
        utils_tests
        gtest
        gtest_main
        game
        boost_system
        boost_timer
        pthread
        Irrlicht
        GL
        Xxf86vm
        X11
    )
endif ()
