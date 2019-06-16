project(client)

if (WIN32)
    include_directories(
        "C:/Boost/include/boost-1_70"
        ../lib/include
        ./include
        ../game/include
        ../utils/include
        ../server/include
        ../error/include
        ../sfx/include
    )
    set(CMAKE_CXX_FLAGS "-D_WIN32_WINNT=0x0601 /EHsc")
else ()
    include_directories(
        ../lib/include
        ./include
        ../game/include
        ../utils/include
        ../server/include
        ../error/include
        ../sfx/include
    )
    set(CMAKE_CXX_FLAGS "-g3")

endif ()

add_library(client
    STATIC
    ./srcs/Client.cpp
    ./srcs/Clock.cpp
    ./srcs/Core.cpp
    ./srcs/Entity.cpp
    ./srcs/Graphic.cpp
    ./srcs/GraphicLoader.cpp
    ./srcs/LogicPause.cpp
    ./srcs/CustomMenu.cpp
    ./srcs/MenuEvent.cpp
)

if (WIN32)
    FIND_PACKAGE(Boost 1.70 REQUIRED COMPONENTS filesystem regex PATHS "C:/Boost")

    IF (Boost_FOUND)
        # INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
        ADD_DEFINITIONS( "-DHAS_BOOST" )
    ENDIF()

    set_property(TARGET client PROPERTY CXX_STANDARD 11)
    target_include_directories(client INTERFACE
        "C:/Boost/include/boost-1_70"
        ../lib/include
        ./include
        ../game/include
        ../utils/include
        ../server/include
        ../error/include
        ../sfx/include
    )
    target_link_libraries(
        client
        game
        error
        utils
        bot
        sfx
    )
else ()
    target_include_directories(client INTERFACE
        ../lib/include
        ./include
        ../game/include
        ../utils/include
        ../server/include
        ../error/include
        ../sfx/include
    )
    target_link_libraries(
        client
        game
        error
        utils
        sfx
        boost_system
        pthread
        boost_timer
        GL
        Xxf86vm
        X11
    )
endif ()

SET_TARGET_PROPERTIES(client PROPERTIES LINKER_LANGUAGE CXX)

# add_subdirectory(tests)
