project(game)

add_library(game
    STATIC
    ./src/Bomb.cpp
    ./src/Character.cpp
    ./src/Entity.cpp
    ./src/EntityManager.cpp
    )

target_include_directories(game INTERFACE ./include)
SET_TARGET_PROPERTIES(game PROPERTIES LINKER_LANGUAGE CXX)

# add_subdirectory(tests)