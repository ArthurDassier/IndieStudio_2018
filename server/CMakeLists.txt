project(server)

include_directories(
    ./include
    ../game/include
    ../lib/include
)

add_library(server
    STATIC
    ./src/room.cpp
    ./src/server.cpp
    ./src/session.cpp
)

target_include_directories(server INTERFACE
    ./include
    ../game/include
    ../lib/include
)

target_link_libraries(
    server
    game
)

SET_TARGET_PROPERTIES(server PROPERTIES LINKER_LANGUAGE CXX)

set_property(TARGET server PROPERTY CXX_STANDARD 17)

add_subdirectory(tests)
