project(server)

include_directories(
    ./includes
    ../game/includes
    ../lib/includes
)

add_library(server
    STATIC
    ./srcs/Room.cpp
    ./srcs/Server.cpp
    ./srcs/Session.cpp
)

target_include_directories(server INTERFACE
    ./includes
    ../game/includes
    ../lib/includes
)

target_link_libraries(
    server
    game
)

SET_TARGET_PROPERTIES(server PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(tests)
