project(client)

if (WIN32)
    include_directories(
        "C:/Boost/include/boost-1_70"
    )
    set(CMAKE_CXX_FLAGS "-D_WIN32_WINNT=0x0601 /EHsc")
endif ()

include_directories(
    ../lib/include
    ./include
    ../game/include
    ../utils/include
    ../error/include
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

if (WIN32)
    FIND_PACKAGE(Boost 1.70 REQUIRED COMPONENTS filesystem regex PATHS "C:/Boost")

    IF (Boost_FOUND)
        # INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
        ADD_DEFINITIONS( "-DHAS_BOOST" )
    ENDIF()

    set_property(TARGET client PROPERTY CXX_STANDARD 11)
    target_include_directories(bomberman PRIVATE "C:/Boost/include/boost-1_70")
    target_include_directories(client INTERFACE ./include)

    target_link_libraries(
        client
        game
        error
    )
else ()
    target_link_libraries(
        client
        game
        error
        utils
        boost_system
        pthread
        boost_timer
        GL
        Xxf86vm
        X11
    )
endif ()

target_include_directories(client INTERFACE ./include ../lib/include)

SET_TARGET_PROPERTIES(client PROPERTIES LINKER_LANGUAGE CXX)

# add_subdirectory(tests)
