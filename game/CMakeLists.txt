project(game)

include_directories(
    ../lib/include
    ./include
)

add_library(game STATIC
    ./src/Bomb.cpp
    ./src/Character.cpp
    ./src/Entity.cpp
    ./src/EntityManager.cpp
    )

SET_TARGET_PROPERTIES(game PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(tests)
