project(error)

include_directories(
    ./include
)

add_library(error
    STATIC
    ./srcs/Error.cpp
)

target_include_directories(error INTERFACE
    ./include
)

SET_TARGET_PROPERTIES(error PROPERTIES LINKER_LANGUAGE CXX)

# add_subdirectory(tests)
