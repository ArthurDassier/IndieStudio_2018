add_executable(
    bomberman
    src/main.cpp
)

set_target_properties(bomberman PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

target_link_libraries(bomberman module_tmp)
