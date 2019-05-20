project(module_tmp_tests)

add_executable(
    module_tmp_tests
    test.cpp
)

set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-lgcov")
# add_custom_target(module_tmp_tests COMMAND "-coverage")
# target_compile_options²(module_tmp_tests INTERFACE --coverage)
# set(CMAKE_CXX_OUTPUT_ENTENSION_REPLACE ON)
# set(CMAKE_EXE_LINKER "-fprofile-arcs -ftest-coverage")

set_target_properties(module_tmp_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

target_link_libraries(module_tmp_tests gtest gtest_main module_tmp)
