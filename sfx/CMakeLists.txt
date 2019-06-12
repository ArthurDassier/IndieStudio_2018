project(sfx)

include_directories(
    ./include
)

add_library(sfx
    STATIC
    ./srcs/Audio.cpp
    ./srcs/SFX.cpp
)

target_include_directories(sfx INTERFACE
    ./include()
)

target_link_libraries(
    sfx
    utils
    sfml-audio
)

SET_TARGET_PROPERTIES(sfx PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(tests)