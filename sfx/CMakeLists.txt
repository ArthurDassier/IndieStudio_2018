project(sfx)

if (WIN32)
    include_directories(./include)
    set(CMAKE_CXX_FLAGS "-D_WIN32_WINNT=0x0601 /EHsc")
else ()
    include_directories(./include)
endif ()

add_library(sfx
    STATIC
    ./srcs/Audio.cpp
    ./srcs/SFX.cpp
)

if (WIN32)
    #FOUND SFML
    target_include_directories(sfx INTERFACE
        #"C:SFML" ...
        ./include
    )
    target_link_libraries(
        sfx
        utils
    )
else ()
    target_include_directories(sfx INTERFACE
        ./include
    )
    target_link_libraries(
        sfx
        utils
        sfml-audio
    )
endif ()

SET_TARGET_PROPERTIES(sfx PROPERTIES LINKER_LANGUAGE CXX)

# add_subdirectory(tests)
