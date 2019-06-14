project(server)

if (WIN32)
    include_directories(
        "C:/Boost/include/boost-1_70"
        ./include
        ../game/include
        ../lib/include
    )
    set(CMAKE_CXX_FLAGS "-D_WIN32_WINNT=0x0601 /EHsc")
else ()
    include_directories(
        ./include
        ../game/include
        ../lib/include
    )
endif ()

add_library(server
    STATIC
    ./srcs/Room.cpp
    ./srcs/Server.cpp
    ./srcs/Session.cpp
)

if (WIN32)
    target_include_directories(server
        INTERFACE
        ./include
        "C:/Boost/include/boost-1_70"
        ../lib/include
        ../game/include
    )
else ()
    target_include_directories(server
        INTERFACE
        ./include
        ../game/include
        ../lib/include
    )
endif ()

target_link_libraries(
    server
    game
    utils
    error
)

SET_TARGET_PROPERTIES(server PROPERTIES LINKER_LANGUAGE CXX)

# add_subdirectory(tests)
