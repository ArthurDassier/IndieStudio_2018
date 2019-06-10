project(server)

include_directories(
    ./include
    ../game/include
    ../lib/include
)

add_library(server
    STATIC
    ./srcs/Room.cpp
    ./srcs/Server.cpp
    ./srcs/Session.cpp
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

add_subdirectory(tests)
