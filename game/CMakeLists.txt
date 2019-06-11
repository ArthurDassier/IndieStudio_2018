project(game)

if (WIN32)
    include_directories(
        "C:/Boost/include/boost-1_70"
    )
endif ()

include_directories(
    ../lib/include
    ./include
    ../server/include
)

add_library(game STATIC
    ./srcs/Bomb.cpp
    ./srcs/Character.cpp
    ./srcs/Entity.cpp
    ./srcs/EntityManager.cpp
    ./srcs/Game.cpp
    ./srcs/Generation.cpp
)

target_link_libraries(
    game
    utils
)

SET_TARGET_PROPERTIES(game PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(tests)
