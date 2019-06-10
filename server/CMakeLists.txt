project(server)

add_library(server
    STATIC
    ./src/room.cpp
    ./src/server.cpp
    ./src/session.cpp
    ../game/src/Character.cpp
    ../game/src/Entity.cpp
    ../game/src/Game.cpp
    ../utils/src/Packet.cpp
    )

target_include_directories(server INTERFACE ./include)
SET_TARGET_PROPERTIES(server PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(tests)
