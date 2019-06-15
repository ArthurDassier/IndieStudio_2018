project(game)

if (WIN32)
    include_directories(
        ./include
        "C:/Boost/include/boost-1_70"
        ../lib/include
        ../server/include
    )
    set(CMAKE_CXX_FLAGS "-D_WIN32_WINNT=0x0601 /EHsc")
else ()
    include_directories(
        ./include
        ../lib/include
        ../server/include
    )
    set(CMAKE_CXX_FLAGS "-g3")
endif ()

add_library(game STATIC
    ./srcs/Block.cpp
    ./srcs/Bomb.cpp
    ./srcs/BrittleBlock.cpp
    ./srcs/Ground.cpp
    ./srcs/Character.cpp
    ./srcs/Entity.cpp
    ./srcs/EntityManager.cpp
    ./srcs/Game.cpp
    ./srcs/Generation.cpp
    ./srcs/Bot.cpp
)

if (WIN32)
    target_include_directories(game INTERFACE
        ./include
        "C:/Boost/include/boost-1_70"
        ../lib/include
        ../server/include
    )
else ()
    target_include_directories(game INTERFACE
        ./include
        ../lib/include
        ../server/include
    )
endif ()

target_link_libraries(
    game
    utils
    error
    bot
)

SET_TARGET_PROPERTIES(game PROPERTIES LINKER_LANGUAGE CXX)

# add_subdirectory(tests)
