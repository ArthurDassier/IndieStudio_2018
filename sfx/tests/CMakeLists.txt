project(sfx_tests)

LINK_DIRECTORIES (
    ../../lib
)

include_directories(
    ../../lib/include
)

add_executable(
    sfx_tests
    tests_audio.cpp
    tests_music.cpp
    tests_sound.cpp
)

set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-lgcov")
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -no-pie")

set_target_properties(sfx_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

target_link_libraries(
    sfx_tests
    gtest
    gtest_main
    sfx
    pthread
)
