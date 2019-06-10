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

set_property(TARGET game PROPERTY CXX_STANDARD 17)

add_subdirectory(tests)
