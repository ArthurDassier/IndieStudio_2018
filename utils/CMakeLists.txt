project(utils)

include_directories(./include)

add_library(utils
    STATIC
    ./srcs/ConfigManager.cpp
    ./srcs/Packet.cpp
)

target_include_directories(utils INTERFACE ./include)
SET_TARGET_PROPERTIES(utils PROPERTIES LINKER_LANGUAGE CXX)

# add_subdirectory(tests)