project(server)

if (WIN32)
    include_directories(
        "C:/Boost/include/boost-1_70"
    )
    set(CMAKE_CXX_FLAGS "-D_WIN32_WINNT=0x0601 /EHsc")
endif ()

include_directories(
    ./include
    ../game/include
    ../lib/include
    ../error/include
)

add_library(server
    STATIC
    ./srcs/Room.cpp
    ./srcs/Server.cpp
    ./srcs/Session.cpp
)

target_include_directories(server
    INTERFACE
    ./include
    ../game/include
    ../lib/include
)

target_link_libraries(
    server
    game
    utils
    error
)

SET_TARGET_PROPERTIES(server PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(tests)
