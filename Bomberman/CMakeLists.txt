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

if (WIN32)
    include_directories(
        "C:/Boost/include/boost-1_70"
    )
    link_directories("C:/Boost/lib")

    FIND_PACKAGE(Boost 1.70 REQUIRED COMPONENTS filesystem regex PATHS "C:/Boost")
    if (Boost_FOUND)
      # INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
      ADD_DEFINITIONS( "-DHAS_BOOST" )
    endif ()
    set_property(TARGET bomberman PROPERTY CXX_STANDARD 17)
    target_include_directories(bomberman INTERFACE "C:/Boost/include/boost-1_70")
    target_include_directories(bomberman INTERFACE "C:/Boost/lib")
    target_include_directories(bomberman INTERFACE ./include)
endif ()

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
    game
    utils
    GL
    Xxf86vm
    X11
    sfml-audio
)
