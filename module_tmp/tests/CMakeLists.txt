project(module_tmp_tests)

add_executable(
    module_tmp_tests
    test.cpp
)

set_target_properties(module_tmp_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

target_link_libraries(module_tmp_tests gtest gtest_main module_tmp)
