project(client)

include_directories(
    ../lib/include
    ./include
)

add_library(client STATIC
    ./srcs/Client.cpp
    ./srcs/Core.cpp
    ./srcs/Entity.cpp
    ./srcs/Graphic.cpp
    ./srcs/Clock.cpp
    )

target_include_directories(client INTERFACE ./include ../lib/include)

SET_TARGET_PROPERTIES(client PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(
    client
    boost_system
    pthread
    boost_timer
    GL
    Xxf86vm
    X11
)

add_subdirectory(tests)
