LINK_DIRECTORIES (
    ./lib
)

LINK_DIRECTORIES (
    ../lib
)

add_executable(
    bomberman
    src/main.cpp
)

set_property(TARGET bomberman PROPERTY CXX_STANDARD 17)

set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -no-pie")

set_target_properties(bomberman PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

target_link_libraries(
    bomberman
    boost_system
    pthread
    client
    boost_timer
    Irrlicht
    server
    GL
    Xxf86vm
    X11
    sfml-audio
)
