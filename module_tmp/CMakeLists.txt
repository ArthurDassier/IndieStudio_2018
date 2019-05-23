project(module_tmp)

add_library(module_tmp STATIC
    ./src/toto.cpp
    )

target_include_directories(module_tmp INTERFACE ./include)

SET_TARGET_PROPERTIES(module_tmp PROPERTIES LINKER_LANGUAGE CXX)

# target_include_directories(module_tmp STATIC ./include)
# target_link_libraries(module_tmp STATIC)

add_subdirectory(tests)
