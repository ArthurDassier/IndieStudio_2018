project(client)

include_directories(
    ../lib/include
    ./include
    ../game/include
    ../utils/include
)

add_library(client
    STATIC
    ./srcs/Client.cpp
    ./srcs/Clock.cpp
    ./srcs/Core.cpp
    ./srcs/Entity.cpp
    ./srcs/Graphic.cpp
    ./srcs/GraphicLoader.cpp
    ./srcs/LogicPause.cpp
)

target_include_directories(client INTERFACE ./include ../lib/include)

target_link_libraries(
    client
    game
    utils
    boost_system
    pthread
    boost_timer
    GL
    Xxf86vm
    X11
)

SET_TARGET_PROPERTIES(client PROPERTIES LINKER_LANGUAGE CXX)
    
add_subdirectory(tests)
