LINK_DIRECTORIES (
    ./lib
)

add_executable(
    bomberman
    src/main.cpp
)

set (CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -no-pie")

set_target_properties(bomberman PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

target_link_libraries(
    bomberman
    boost_system
    boost_timer
    pthread
    module_tmp
    client
    Irrlicht
    server
    GL
    Xxf86vm
    Xext
    X11
    Xcursor
)
