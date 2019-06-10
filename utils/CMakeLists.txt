project(utils)

add_library(utils STATIC
    # ./src/ConfigManager.cpp
    ./src/Packet.cpp
    )

target_include_directories(utils INTERFACE ./include)
SET_TARGET_PROPERTIES(utils PROPERTIES LINKER_LANGUAGE CXX)

# add_subdirectory(tests)