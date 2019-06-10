project(game)

include_directories(
    ../lib/include
    ./include
)

add_library(game STATIC
    ./srcs/Bomb.cpp
    ./srcs/Character.cpp
    ./srcs/Entity.cpp
    ./srcs/EntityManager.cpp
<<<<<<< HEAD
=======
    ./srcs/Generation.cpp
>>>>>>> master
    )

SET_TARGET_PROPERTIES(game PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(tests)
