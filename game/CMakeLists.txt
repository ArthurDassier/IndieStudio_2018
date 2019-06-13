project(game)

include_directories(
    ../lib/include
    ./include
    ../server/include
    ../error/include
)

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
)

target_link_libraries(
    game
    utils
    error
)

set(CMAKE_CXX_FLAGS "-g3")

SET_TARGET_PROPERTIES(game PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(tests)
